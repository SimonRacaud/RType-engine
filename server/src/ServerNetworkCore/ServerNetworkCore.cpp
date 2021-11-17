/*
** EPITECH PROJECT , 2021
** ServerNetworkCore
** File description:
** \file ServerNetworkCore.cpp
** \author simon
** \brief
** \date 15/11/2021
*/

#include <tuple>
#include "ServerNetworkCore.hpp"
#include "ServerCore/ServerCore.hpp"

using namespace std;

bool ServerNetworkCore::_loop = true;

void ServerNetworkCore::sig_handler(int)
{
    ServerNetworkCore::_loop = false;
}

ServerNetworkCore::ServerNetworkCore()
try :
    _tcpServer(shared_ptr<IConnection>(make_shared<AsioServerTCP>(ServerCore::config->getVar<int>("PORT_TCP")))),
    _udpServer(shared_ptr<IConnection>(make_shared<AsioServerUDP>(ServerCore::config->getVar<int>("PORT_UDP")))),
    _garbageEntity(ServerCore::config->getVar<std::pair<int, int>>("WINDOW_SIZE")),
    _maxRoomClient(ServerCore::config->getVar<int>("MAX_CLIENT_ROOM"))
{
    this->_roomFreeIds.resize(ServerCore::config->getVar<int>("ROOM_MAX"));
    std::iota(std::begin(_roomFreeIds), std::end(_roomFreeIds), 0);
    signal(SIGINT, ServerNetworkCore::sig_handler);
} catch (std::exception const &e) {
    std::cerr << "FATAL ERROR : network server connection init failed. " << e.what() << std::endl;
    exit(84); // TODO : to improve
}

void ServerNetworkCore::createEntity(size_t roomId, const std::string &type,
    netVector2f const& position, netVector2f const& velocity)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    Tram::CreateEntityRequest tram(roomId, type, GET_NOW, position, velocity);

    this->_tcpServer.send(tram, room->masterClient.ip, room->masterClient.port);
}

void ServerNetworkCore::destroyEntity(size_t roomId, NetworkId id)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    Tram::DestroyEntity tram(roomId, id);

    for (Network::InfoConnection const &client : room->clients) {
        this->_tcpServer.send(tram, client.ip, client.port);
    }
}

void ServerNetworkCore::syncComponent(size_t roomId, NetworkId id,
    std::type_index const &componentType, size_t componentSize, void *component)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    long int timestamp = GET_NOW;
    Tram::ComponentSync tram(roomId, id, timestamp, componentType, componentSize, component);

    for (Network::InfoConnection const &client : room->clients) {
        this->_tcpServer.send(tram, client.ip, client.port);
    }
}

void ServerNetworkCore::receiveLoop()
{
    while (_loop) {
        try {
            this->_receiveFromChannel(this->_tcpServer);
        } catch (std::exception const &e) {
            std::cerr << "ServerNetworkCore::receiveLoop : tcp error" << std::endl;
        }
        try {
            this->_receiveFromChannel(this->_udpServer);
        } catch (std::exception const &e) {
            std::cerr << "ServerNetworkCore::receiveLoop : udp error" << std::endl;
        }
    }
}

void ServerNetworkCore::_receiveFromChannel(NetworkManager &net)
{
    auto [buffer, client] = net.receive();

    if (buffer == nullptr) {
        return; // abort
    }
    Tram::Serializable header;
    header.deserialize(buffer);
    if (header.magic != MAGIC) {
        throw std::runtime_error("ServerNetworkCore::_receiveFromChannel invalid magic number");
    }
    InfoConnection info(std::get<0>(client), std::get<1>(client));
    this->_tramHandler(header, info, buffer);
}

void ServerNetworkCore::_tramHandler(Tram::Serializable &header, InfoConnection &info,
    uint8_t *buffer)
{
    switch (header.type) {
        case Tram::TramType::GET_ROOM_LIST: {
            this->receiveGetRoomList(info);
            break;
        }
        case Tram::TramType::CREATE_ROOM: {
            this->receiveCreateRoom(info);
            break;
        }
        case Tram::TramType::JOIN_ROOM: {
            Tram::JoinRoom data;
            data.deserialize(buffer);
            this->receiveJoinRoom(info, data);
            break;
        }
        case Tram::TramType::QUIT_ROOM: {
            this->receiveQuitRoom(info);
            break;
        }
        case Tram::TramType::CREATE_ENTITY_REQUEST: {
            Tram::CreateEntityRequest data;
            data.deserialize(buffer);
            this->receiveCreateEntityRequest(info, data);
            break;
        }
        case Tram::TramType::CREATE_ENTITY_REPLY: {
            Tram::CreateEntityReply data;
            data.deserialize(buffer);
            this->receiveCreateEntityReply(info, data);
            break;
        }
        case Tram::TramType::DESTROY_ENTITY: {
            Tram::DestroyEntity data;
            data.deserialize(buffer);
            this->receiveDestroyEntity(info, data);
            break;
        }
        case Tram::TramType::SYNC_COMPONENT: {
            Tram::ComponentSync data;
            data.deserialize(buffer);
            this->receiveSyncComponent(info, data);
            break;
        }
        default:
            throw std::runtime_error("ServerNetworkCore::_tramHandler invalid tram type");
    }
}

void ServerNetworkCore::receiveGetRoomList(InfoConnection &info)
{
    std::vector<size_t> roomList;

    for (shared_ptr<NetworkRoom> const &room : _rooms) {
        roomList.push_back(room->roomId);
    }
    Tram::GetRoomList tram(roomList);
    this->_udpServer.send(tram, info.ip, info.port);
}

void ServerNetworkCore::receiveCreateRoom(InfoConnection &info)
{
    if (this->_roomFreeIds.empty()) {
        Tram::JoinCreateRoomReply tram(false);
        this->_udpServer.send(tram, info.ip, info.port);
    } else {
        size_t roomId = this->_roomFreeIds.back();

        this->_roomFreeIds.pop_back();
        this->_rooms.push_back(std::make_shared<NetworkRoom>(roomId, info));
        // CREATE ROOM
        this->_roomManager.createRoom(roomId);
        // END
        Tram::JoinRoom data(roomId);
        this->receiveJoinRoom(info, data);
    }
}

void ServerNetworkCore::receiveJoinRoom(InfoConnection &info, Tram::JoinRoom &data)
{
    size_t roomId = data.roomId;
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);

    if (room->clients.size() >= _maxRoomClient || room->startTimestamp >= GET_NOW) {
        Tram::JoinCreateRoomReply tram(false, roomId);
        this->_udpServer.send(tram, info.ip, info.port);
    } else {
        Tram::JoinCreateRoomReply tram(true, roomId, room->startTimestamp, (room->clients.size() + 1));
        this->_udpServer.send(tram, info.ip, info.port);
        room->clients.push_back(info);
    }
}

void ServerNetworkCore::receiveQuitRoom(InfoConnection &info)
{
    size_t counter = 0;
    for (shared_ptr<NetworkRoom> &room : _rooms) {
        auto it = std::find_if(room->clients.begin(), room->clients.end(), [info](InfoConnection const &item) {
            return info.ip == item.ip && info.port == item.port;
        });
        if (it != room->clients.end()) {
            size_t clientIndex = (it - room->clients.begin());
            room->clients.erase(it);
            /// Remove the player on other clients:
            this->_removePlayer(room, clientIndex);
            if (room->clients.empty()) {
                // CLOSE ROOM
                this->_roomManager.deleteRoom(room->roomId);
                // END
                this->_roomFreeIds.push_back(room->roomId); // the room id is free again
                this->_rooms.erase(this->_rooms.begin() + counter); // remove the room
            }
            break;
        }
    }
    counter++;
}

void ServerNetworkCore::_removePlayer(shared_ptr<NetworkRoom> &room, size_t clientIndex)
{
    // find player network id
    auto itPlayerNetId = std::find_if(room->clientPlayerNetworkIds.begin(), room->clientPlayerNetworkIds.end(),
        [clientIndex](std::tuple<size_t, NetworkId> const& el) {
            return std::get<0>(el) == clientIndex;
        });

    if (itPlayerNetId != room->clientPlayerNetworkIds.end()) {
        // send remove request to all clients
        NetworkId playerNetId = std::get<1>(*itPlayerNetId);
        this->destroyEntity(room->roomId, playerNetId);
    } else {
        std::cerr << "ServerNetworkCore::_removePlayer Cannot remove client's player. player not found." << std::endl;
    }
}

void ServerNetworkCore::receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    // Intercept and Save client player's network id:
    if (string(data.entityType) == "Player") {
        for (size_t i = 0; i < room->clients.size(); i++) {
            if (room->clients[i].ip == string(data.ip) && room->clients[i].port == data.port) {
                room->clientPlayerNetworkIds.push_back(std::make_tuple(i, data.networkId));
                break;
            }
        }
    }
    if (room->masterClient == info) {
        if (data.entityId == -1) {
            // The request came from the server
            if (data.accept == true ) {
                if (string(data.entityType) == "Enemy") {
                    this->_roomManager.createEntityEnemy(data.roomId, data.networkId);
                    // TODO : if enemy, call enemy manager (save network id)
                }
                // Broadcast entity creation to all slave clients
                Tram::CreateEntityRequest tram(data.roomId, data.networkId, data.entityType, data.timestamp,
                    data.position, data.velocity);
                for (InfoConnection const &client : room->clients) {
                    if (!(client == info)) { // not master client
                        this->_tcpServer.send(data, client.ip, client.port);
                    }
                }
            }
        } else {
            // The request came from a slave client
            // redirect response to the source emitter
            this->_tcpServer.send(data, data.ip, data.port);
        }
    } else {
        // impossible (the response come from a slave client)
        throw std::runtime_error("ServerNetworkCore::receiveCreateEntityReply bad response owner");
    }
}

void ServerNetworkCore::receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    if (room->masterClient == info) {
        /// Request from master client
        // => broadcast to others clients
        for (InfoConnection const &client : room->clients) {
            if (!(client == info)) { // not master client
                this->_tcpServer.send(data, client.ip, client.port);
            }
        }
    } else {
        /// Request from slave client
        // => redirect to master client
        Tram::CreateEntityRequest tram(data.roomId, data.id, data.entityType,
            data.timestamp, info.port, info.ip, data.position, data.velocity);
        this->_tcpServer.send(tram, room->masterClient.ip, room->masterClient.port);
    }
}

void ServerNetworkCore::receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    if (room->masterClient == info) {
        /// Request from master client
        // TODO - if enemy => remove him ? (on server)
        // => broadcast to others clients
        for (InfoConnection const &client : room->clients) {
            if (!(client == info)) { // not master client
                this->_tcpServer.send(data, client.ip, client.port);
            }
        }
    } else {
        /// Request from slave client - Forbidden
        std::cerr << "ServerNetworkCore::receiveDestroyEntity A client is cheating ! Ignore request" << std::endl;
    }
}

void ServerNetworkCore::receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    // From Master client : must be a component from a player entity, a bullet, equipment.
    // From Slave client : must be a component from a player entity.

    // => Broadcast to other clients
    for (InfoConnection const &client : room->clients) {
        if (!(client == info)) { // not emitter client
            this->_tcpServer.send(data, client.ip, client.port);
        }
    }
    // intercept Position component here (remove if out of bound)
    this->_garbageEntity.processing(data, *this);
}

shared_ptr<NetworkRoom> ServerNetworkCore::_getRoom(size_t roomId)
{
    auto it = std::find_if(_rooms.begin(), _rooms.end(), [roomId](shared_ptr<NetworkRoom> &room) {
        return roomId == room->roomId;
    });
    if (it == _rooms.end()) {
        throw std::invalid_argument("ServerNetworkCore::_checkRoomId room id not found");
    }
    return *it;
}