/*
** EPITECH PROJECT , 2021
** ClientNetworkCore
** File description:
** \file ClientNetworkCore.cpp
** \author simon
** \brief
** \date 15/11/2021
*/

#include "ClientNetworkCore.hpp"

ClientNetworkCore::ClientNetworkCore(Engine::IGameEngine &engine)
    : _engine(engine)
{
    try {
        std::string serverIp = GameCore::config->getVar<std::string>("SERVER_IP");
        size_t serverPort = GameCore::config->getVar<size_t>("SERVER_PORT");

        this->_tcpClient.connect(serverIp, serverPort);
        this->_udpClient.connect(serverIp, serverPort);
    } catch (std::exception const &e) {
        std::cerr << "FATAL ERROR, server connection fail." << std::endl;
        exit(84); // TUEZ LEEEE !!! WHAHAHAHAH
    }
    SHOW_DEBUG("NETWORK: connected to server");
}

ClientNetworkCore::~ClientNetworkCore() {}

void ClientNetworkCore::getRoomList()
{
    Tram::Serializable tram(Tram::TramType::ROOM_LIST);
    this->_udpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send get room list");
}

void ClientNetworkCore::createRoom()
{
    Tram::Serializable tram(Tram::TramType::CREATE_ROOM);
    this->_udpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send create room");
}

void ClientNetworkCore::joinRoom(size_t id)
{
    Tram::JoinRoom tram(id);
    this->_udpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: join room " + std::to_string(id));
}

void ClientNetworkCore::quitRoom()
{
    this->_checkRoom();
    Tram::Serializable tram(Tram::TramType::QUIT_ROOM);
    this->_udpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send quit room");
}

void ClientNetworkCore::createEntity(Engine::Entity entity, std::string type)
{
    this->_checkRoom();
    long int timestamp = GET_NOW;
    Tram::CreateEntityRequest tram(this->_roomId, entity, type, timestamp);
    this->_tcpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send create entity");
}

void ClientNetworkCore::destroyEntity(Engine::NetworkId id)
{
    this->_checkRoom();
    Tram::DestroyEntity tram(this->_roomId, id);
    this->_tcpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send destroy entity");
}

void ClientNetworkCore::syncComponent(Engine::NetworkId id, std::type_index const &componentType,
    size_t componentSize, void *component)
{
    this->_checkRoom();
    long int timestamp = GET_NOW;
    Tram::ComponentSync tram(this->_roomId, id, timestamp, componentType, componentSize, component);
    this->_udpClient.sendAll(tram);
    SHOW_DEBUG("NETWORK: send sync component entity-net-id=" + to_string(id) + " comp-type="
        + to_string(componentType.hash_code()));
}

void ClientNetworkCore::receiveRoomList(InfoConnection &info, Tram::GetRoomList &data)
{
    SHOW_DEBUG("NETWORK: receive - game room list");
    // TODO
}

void ClientNetworkCore::receiveJoinRoomReply(InfoConnection &info, Tram::JoinCreateRoomReply &data)
{
    SHOW_DEBUG("NETWORK: receive - join/create room reply");
    // TODO
}

void ClientNetworkCore::receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data)
{
    SHOW_DEBUG("NETWORK: receive - create entity reply");
    // TODO TCP
}

void ClientNetworkCore::receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data)
{
    SHOW_DEBUG("NETWORK: receive - create entity reply");
    // TODO TCP
}

void ClientNetworkCore::receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data)
{
    SHOW_DEBUG("NETWORK: receive - receive sync component");
    // TODO
}

void ClientNetworkCore::receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data)
{
    SHOW_DEBUG("NETWORK: receive - destroy entity");
    // TODO TCP
}

void ClientNetworkCore::receiveLoop()
{
    while (this->_loop) {
        try {
            this->_receiveTcp();
        } catch (std::exception const &e) {
            // TODO
        }
        try {
            this->_receiveUdp();
        } catch (std::exception const &e) {
            // TODO
        }
    }
}

void ClientNetworkCore::quit()
{
    this->_loop = false;
}

void ClientNetworkCore::_receiveTcp()
{
    auto [buffer, client] = this->_tcpClient.receive();

    if (buffer == nullptr) {
        return;
    }
    this->_tramExtractor(buffer, client);
}

void ClientNetworkCore::_receiveUdp()
{
    auto [buffer, client] = this->_udpClient.receive();

    if (buffer == nullptr) {
        return;
    }
    this->_tramExtractor(buffer, client);
}

void ClientNetworkCore::_tramExtractor(
    uint8_t *buffer, std::pair<std::string, std::size_t> &client)
{
    Tram::Serializable header;
    header.deserialize(buffer);
    if (header.magic != MAGIC) {
        throw std::runtime_error("ClientNetworkCore::_tramExtractor invalid magic number");
    }
    InfoConnection info(std::get<0>(client), std::get<1>(client));
    this->_tramHandler(header, info, buffer);
}

void ClientNetworkCore::_tramHandler(Tram::Serializable &header, InfoConnection &info,
    uint8_t *buffer)
{
    switch (header.type) {
        case Tram::TramType::ROOM_LIST: {
            Tram::GetRoomList data;
            data.deserialize(buffer);
            this->receiveRoomList(info, data);
            break;
        }
        case Tram::TramType::JOIN_ROOM_REPLY: {
            Tram::JoinCreateRoomReply data;
            data.deserialize(buffer);
            this->receiveJoinRoomReply(info, data);
            break;
        }
        case Tram::TramType::CREATE_ENTITY: {
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
            throw std::runtime_error("ClientNetworkCore::_tramHandler invalid tram type");
    }
}

void ClientNetworkCore::_checkRoom()
{
    if (_roomId == NO_ROOM) {
        throw std::runtime_error("ClientNetworkCore not connected to any room.");
    }
}