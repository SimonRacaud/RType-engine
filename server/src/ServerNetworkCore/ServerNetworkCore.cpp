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
    _portUdp(ServerCore::config->getVar<int>("PORT_UDP")),
    _portTcp(ServerCore::config->getVar<int>("PORT_TCP")),
    _portUdpClient(ServerCore::config->getVar<int>("PORT_UDP_CLIENT")),
    _tcpServer(shared_ptr<IConnection>(make_shared<AsioServerTCP>(_portTcp))),
    _udpServer(shared_ptr<IConnection>(make_shared<AsioServerUDP>(_portUdp))),
    _garbageEntity(ServerCore::config->getVar<std::pair<int, int>>("WINDOW_SIZE"), 100, 0),
    _maxRoomClient(ServerCore::config->getVar<int>("MAX_CLIENT_ROOM"))
{
    PUT_DEBUG("INITIALIZED.");
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
    PUT_DEBUG("[Send] Create entity : roomId=" + to_string(roomId) + ", type=" + type + ".");
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    Tram::CreateEntityRequest tram(roomId, type, GET_NOW, position, velocity);

    try {
        this->_tcpServer.send(tram, room->masterClient.ip);
    } catch (Network::invalidConnection const &) {
        std::cerr << "Unexpected client disconnection." << std::endl;
        this->_closeGameRoom(roomId);
    }
}

void ServerNetworkCore::destroyEntity(size_t roomId, NetworkId id)
{
    PUT_DEBUG("[Send] Destroy entity : roomId=" + to_string(roomId) + ", networkId=" + to_string(id) + ".");
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    Tram::DestroyEntity tram(roomId, id);

    for (Network::InfoConnection const &client : room->clients) {
        try {
            this->_tcpServer.send(tram, client.ip);
        } catch (Network::invalidConnection const &) {
            std::cerr << "Unexpected disconnection send tcp" << std::endl;
        }
    }
}

void ServerNetworkCore::syncComponent(size_t roomId, NetworkId id,
    std::type_index const &componentType, size_t componentSize, void *component)
{
    PUT_DEBUG_SYNC("[Send] Sync component : roomId=" + to_string(roomId) + ", networkId=" + to_string(id)
        + ", componentType=" + to_string(componentType.hash_code()) + ".");
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);
    long int timestamp = GET_NOW;
    Tram::ComponentSync tram(roomId, id, timestamp, componentType, componentSize, component);

    for (Network::InfoConnection const &client : room->clients) {
        try {
            this->_udpServer.send(tram, client.ip, _portUdpClient);
        } catch (Network::invalidConnection const &) {
            std::cerr << "Unexpected client disconnection" << std::endl;
            this->_removeClient(roomId, client.ip);
        }
    }
    // intercept Position component here (remove if out of bound)
    if (componentType.hash_code() == Engine::Position::type.hash_code()) {
        this->_garbageEntity.processing(tram, *this);
    }
}

void ServerNetworkCore::receiveLoop()
{
    while (_loop) {
        try {
            this->_receiveFromChannel(this->_tcpServer);
        } catch (std::exception const &e) {
            //std::cerr << "ServerNetworkCore::receiveLoop : tcp error. " << e.what() << std::endl;
        }
        try {
            this->_receiveFromChannel(this->_udpServer);
        } catch (std::exception const &e) {
            std::cerr << "ServerNetworkCore::receiveLoop : udp error. " << e.what() << std::endl;
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
    PUT_DEBUG_SYNC("Receive packet from IP=" + info.ip + ", PORT=" + to_string(info.port) + ".");
    this->_tramHandler(header, info, buffer);
}

void ServerNetworkCore::_tramHandler(Tram::Serializable &header, InfoConnection &info,
    uint8_t *buffer)
{
    switch (header.type) {
        case Tram::TramType::ROOM_LIST: {
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
    PUT_DEBUG("Receive [GetRoomList].");
    std::vector<size_t> roomList;

    for (shared_ptr<NetworkRoom> const &room : _rooms) {
        roomList.push_back(room->roomId);
    }
    Tram::GetRoomList tram(roomList);
    this->_udpServer.send(tram, info.ip, _portUdpClient);
}

void ServerNetworkCore::receiveCreateRoom(InfoConnection &info)
{
    PUT_DEBUG("Receive [CreateRoom] .");

    if (this->_roomFreeIds.empty()) {
        Tram::JoinCreateRoomReply tram(false);
        this->_udpServer.send(tram, info.ip, _portUdpClient);
        PUT_DEBUG("[CreateRoom] creation refused.");
    } else {
        size_t roomId = this->_roomFreeIds.back();

        this->_roomFreeIds.pop_back();
        this->_rooms.push_back(std::make_shared<NetworkRoom>(roomId, info));
        // CREATE ROOM
        this->_roomManager.createRoom(roomId, this->_rooms.back()->startTimestamp);
        // END
        Tram::JoinRoom data(roomId);
        this->receiveJoinRoom(info, data);
        PUT_DEBUG("[CreateRoom] RoomId="+ to_string(roomId)+" created.");
    }
}

void ServerNetworkCore::receiveJoinRoom(InfoConnection &info, Tram::JoinRoom &data)
{
    PUT_DEBUG("Receive [JoinRoom] roomId="+to_string(data.roomId)+".");
    size_t roomId = data.roomId;
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);

    if (room->clients.size() >= _maxRoomClient || room->startTimestamp <= GET_NOW) {
        Tram::JoinCreateRoomReply tram(false, roomId);
        this->_udpServer.send(tram, info.ip, _portUdpClient);
        PUT_DEBUG("[JoinRoom] refused.");
    } else {
        Tram::JoinCreateRoomReply tram(true, roomId, room->startTimestamp, (room->clients.size() + 1));
        this->_udpServer.send(tram, info.ip, _portUdpClient);
        room->clients.push_back(info);
        PUT_DEBUG("[JoinRoom] accepted.");
    }
}

void ServerNetworkCore::receiveQuitRoom(InfoConnection &info)
{
    PUT_DEBUG("Receive [QuitRoom] IP="+info.ip+", PORT="+to_string(info.port)+".");
    size_t counter = 0;
    for (shared_ptr<NetworkRoom> &room : _rooms) {
        auto it = std::find_if(room->clients.begin(), room->clients.end(), [&info](InfoConnection const &item) {
            return info.ip == item.ip && info.port == item.port;
        });
        if (it != room->clients.end()) {
            size_t clientIndex = (it - room->clients.begin());
            room->clients.erase(it);
            /// Remove the player on other clients:
            this->_removePlayer(room, clientIndex);
            PUT_DEBUG("[QuitRoom] The client quit roomId="+ to_string(room->roomId) +".");
            if (room->clients.empty()) {
                this->_closeGameRoom(room->roomId);
            }
            break;
        }
    }
    counter++;
}

void ServerNetworkCore::_removePlayer(shared_ptr<NetworkRoom> &room, size_t clientIndex)
{
    PUT_DEBUG("Remove player.");
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
    PUT_DEBUG("Receive [CreateEntityReply] roomId="+ to_string(data.roomId) +", entity="+data.entityType
        +", accept="+to_string(data.accept)+", networkId="+to_string(data.networkId)
        +", entityId="+to_string(data.entityId)+".");
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    // Intercept and Save client player's network id:
    if (string(data.entityType) == "Player") {
        for (size_t i = 0; i < room->clients.size(); i++) {
            if (room->clients[i].ip == string(data.ip) && room->clients[i].port == data.port) {
                room->clientPlayerNetworkIds.push_back(std::make_tuple(i, data.networkId));
                PUT_DEBUG("[CreateEntityReply] Intercept player.");
                break;
            }
        }
    }
    if (room->masterClient == info) {
        if (data.entityId == -1) {
            // The request came from the server
            if (data.accept == true ) {
                if (string(data.entityType) == string("Enemy")) {
                    PUT_DEBUG("[CreateEntityReply] Create entity enemy.");
                    this->_roomManager.createEntityEnemy(data.roomId, data.networkId);
                }
                // Broadcast entity creation to all slave clients
                Tram::CreateEntityRequest tram(data.roomId, data.networkId, data.entityType, data.timestamp,
                    data.position, data.velocity);
                for (InfoConnection const &client : room->clients) {
                    if (!(client == info)) { // not master client
                        this->_tcpServer.send(data, client.ip);
                    }
                }
            }
        } else {
            // The request came from a slave client
            // redirect response to the source emitter
            this->_tcpServer.send(data, data.ip);
        }
    } else {
        // impossible (the response come from a slave client)
        throw std::runtime_error("ServerNetworkCore::receiveCreateEntityReply bad response owner");
    }
}

void ServerNetworkCore::receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data)
{
    PUT_DEBUG("Receive [CreateEntityRequest] roomId="+to_string(data.roomId)+", entity="+data.entityType
        +", id="+to_string(data.id)+".");
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    if (room->masterClient == info) {
        /// Request from master client
        // => broadcast to others clients
        for (InfoConnection const &client : room->clients) {
            if (!(client == info)) { // not master client
                this->_tcpServer.send(data, client.ip);
            }
        }
    } else {
        /// Request from slave client
        // => redirect to master client
        Tram::CreateEntityRequest tram(data.roomId, data.id, data.entityType,
            data.timestamp, info.port, info.ip, data.position, data.velocity);
        this->_tcpServer.send(tram, room->masterClient.ip);
    }
}

void ServerNetworkCore::receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data)
{
    PUT_DEBUG("Receive [DestroyEntity] roomId="+to_string(data.roomId)+", networkId="+to_string(data.networkId)+".");
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    if (room->masterClient == info) {
        /// Request from master client
        this->_roomManager.destroyEntityEnemy(data.roomId, data.networkId);
        // => broadcast to others clients
        for (InfoConnection const &client : room->clients) {
            if (!(client == info)) { // not master client
                this->_tcpServer.send(data, client.ip);
            }
        }
    } else {
        /// Request from slave client - Forbidden
        std::cerr << "ServerNetworkCore::receiveDestroyEntity A client is cheating ! Ignore request" << std::endl;
    }
}

void ServerNetworkCore::receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data)
{
    PUT_DEBUG_SYNC("Receive [SyncComponent] roomId="+to_string(data.roomId)+", networkId="+to_string(data.networkId)
        +", componentType="+to_string(data.componentType)+", componentSize="+to_string(data.componentSize)+".");
    shared_ptr<NetworkRoom> room = this->_getRoom(data.roomId);

    // From Master client : must be a component from a player entity, a bullet, equipment.
    // From Slave client : must be a component from a player entity.

    // => Broadcast to other clients
    for (InfoConnection const &client : room->clients) {
        if (!(client == info)) { // not emitter client
            this->_udpServer.send(data, client.ip, _portUdpClient);
        }
    }
    // intercept Position component here (remove if out of bound)
    if (data.componentType == Engine::Position::type.hash_code()) {
        this->_garbageEntity.processing(data, *this);
    }
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

void ServerNetworkCore::_closeGameRoom(size_t roomId)
{
    auto it = std::find_if(_rooms.begin(), _rooms.end(), [roomId](shared_ptr<NetworkRoom> const& room) {
        return room->roomId == roomId;
    });

    if (it == _rooms.end()) {
        return;
    }
    if (!(*it)->clients.empty()) {
        // send to clients "end-game" notification
        Tram::Serializable tram(Tram::TramType::QUIT_ROOM);
        for (Network::InfoConnection &client : (*it)->clients) {
            this->_udpServer.send(tram, client.ip, _portUdp);
        }
    }
    // CLOSE ROOM
    this->_roomManager.deleteRoom(roomId);
    // END
    this->_roomFreeIds.push_back(roomId); // the room id is free again
    this->_rooms.erase(it); // remove the room
    PUT_DEBUG("[QuitRoom] Closing roomId="+to_string(roomId)+".");
}

void ServerNetworkCore::_removeClient(size_t roomId, const string &ip)
{
    shared_ptr<NetworkRoom> room = this->_getRoom(roomId);

    auto it = std::find_if(room->clients.begin(), room->clients.end(), [ip](const Network::InfoConnection &info) {
        return info.ip == ip;
    });
    if (it != room->clients.end()) {
        room->clients.erase(it);
        if (room->masterClient.ip == ip) {
            this->_closeGameRoom(roomId);
        }
    }
}