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
#include "CustomCluster.hpp"
#include "EngineCore.hpp"
#include "Event/GUI/SelectScene.hpp"
#include "GameCore/GameCore.hpp"
#include "Scene/Game/GameScene.hpp"
#include "Scene/RoomList/RoomListScene.hpp"

ClientNetworkCore::ClientNetworkCore(Engine::IGameEngine &engine)
try : _engine(engine),
    _tcpClient(shared_ptr<IConnection>(make_shared<AsioClientTCP>())),
    _udpClient(shared_ptr<IConnection>(make_shared<AsioClientUDP>(UDP_PORT))),
    _factory(Engine::ClusterName::GAME)
{
    std::string serverIp = GameCore::config->getVar<std::string>("SERVER_IP");
    size_t serverPort = (size_t)GameCore::config->getVar<int>("SERVER_PORT");

    bool loop = true;
    size_t count;
    for (count = 0; loop && count <= MAX_CONNECT_TRY; count++) {
        //break; // TODO : remove that line when the server is ready
        loop = this->_tcpClient.connect(serverIp, serverPort);
        loop = loop || this->_udpClient.connect(serverIp, serverPort);
    }
    if (count == MAX_CONNECT_TRY) {
        throw std::runtime_error("No server connection. Exit.");
    }
    SHOW_DEBUG("NETWORK: connected to server");
} catch (std::exception const &e) {
    std::cerr << "Fatal error ClientNetworkCore::ClientNetworkCore " << e.what() << std::endl;
    exit(84); // TODO TUEZ LEEEE !!! WHAHAHAHAH
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
    this->_isMaster = false;
    SHOW_DEBUG("NETWORK: send quit room");
}

void ClientNetworkCore::createEntity(Engine::Entity entity, std::string type,
    netVector2f const &position, netVector2f const& velocity)
{
    this->_checkRoom();
    long int timestamp = GET_NOW;
    Tram::CreateEntityRequest tram(this->_roomId, entity, type, timestamp, position, velocity);
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

void ClientNetworkCore::receiveRoomList(InfoConnection &, Tram::GetRoomList &data)
{
    SHOW_DEBUG("NETWORK: receive - game room list");
    if (data.nbItem != 0 && this->_engine.getSceneManager().isCurrent<Scene::RoomListScene>()) {
        std::shared_ptr<Engine::IScene> scene = this->_engine.getSceneManager().getCurrent();
        Scene::RoomListScene *ptr = reinterpret_cast<Scene::RoomListScene *>(scene.get());
        std::vector<size_t> roomList;
        for (size_t i = 0; i < data.nbItem; i++) {
            roomList.push_back(data.list[i]);
        }
        ptr->reloadRoomList(roomList);
    }
}

void ClientNetworkCore::receiveJoinRoomReply(InfoConnection &, Tram::JoinCreateRoomReply &data)
{
    SHOW_DEBUG("NETWORK: receive - join/create room reply");
    if (data.accept == true) {
        this->_roomId = data.roomId;
        this->_engine.getSceneManager().select<Scene::GameScene>(); // Go to the game scene
        Scene::GameScene *ptr = reinterpret_cast<Scene::GameScene *>(
            (&this->_engine.getSceneManager().get<Scene::GameScene>())
            );
        ptr->setTimeStart(data.startTimestamp); // set game scene countdown
        if (data.playerNumber == 0) {
            this->_isMaster = true;
        }
        ptr->setPlayerNumber(data.playerNumber);
        // Change scene
        Engine::EngineFactory::getInstance().getEventRegister().registerEvent<SelectScene>(Engine::ClusterName::GAME);
    } else {
        std::cerr << "Room connection refused." << std::endl;
    }
}

bool ClientNetworkCore::isMaster() const
{
    return _isMaster;
}

void ClientNetworkCore::receiveCreateEntityReply(InfoConnection &, Tram::CreateEntityReply &data)
{
    SHOW_DEBUG("NETWORK: receive - create entity reply");
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    if (data.accept) {
        this->_engine.getEntityManager().setNetworkId(data.entityId, data.networkId); // apply network id
    } else {
        // rollback entity creation
        this->_engine.getEntityManager().remove(data.entityId);
    }
}

void ClientNetworkCore::receiveCreateEntityRequest(InfoConnection &, Tram::CreateEntityRequest &data)
{
    SHOW_DEBUG("NETWORK: receive - create entity reply");
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    // build the entity
    if (this->isMaster()) {
        /// Allocate a new network id, create the asked entity, send reply to the server.
        Engine::NetworkId networkId = GameCore::engine.getEntityManager().getNetworkId();
        // TODO uncomment
        //this->_factory.build(data.entityType, networkId, data.position, data.velocity, data.timestamp);
        Tram::CreateEntityReply tram(data.roomId, true, data.id, networkId, data.ip, data.port,
            data.timestamp, data.entityType, data.position, data.velocity);
    } else {
        /// Execute entity creation order
        // TODO uncomment
        //this->_factory.build(data.entityType, data.id, data.position, data.velocity, data.timestamp);
    }
}

void ClientNetworkCore::receiveSyncComponent(InfoConnection &, Tram::ComponentSync &data)
{
    SHOW_DEBUG("NETWORK: receive - receive sync component");
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
//    Engine::Entity id = this->_engine.getEntityManager().getId(data.networkId);
//    void *component = reinterpret_cast<uint8_t *>(&data) + sizeof(Tram::ComponentSync);
    //data.timestamp
    //ComponentRollback::apply(id, data.componentType, component); // TODO
}

void ClientNetworkCore::receiveDestroyEntity(InfoConnection &, Tram::DestroyEntity &data)
{
    SHOW_DEBUG("NETWORK: receive - destroy entity");
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    Engine::Entity id = this->_engine.getEntityManager().getId(data.networkId);
    this->_engine.getEntityManager().remove(id);
}

void ClientNetworkCore::receive()
{
    try {
        this->_receiveTcp();
    } catch (std::exception const &e) {
        std::cerr << "ClientNetworkCore::receiveLoop TCP " << e.what() << std::endl;
    }
    try {
        this->_receiveUdp();
    } catch (std::exception const &e) {
        std::cerr << "ClientNetworkCore::receiveLoop UDP " << e.what() << std::endl;
    }
}

void ClientNetworkCore::receiveLoop()
{
    while (this->_loop) {
        try {
            this->_receiveTcp();
        } catch (std::exception const &e) {
            std::cerr << "ClientNetworkCore::receiveLoop TCP " << e.what() << std::endl;
        }
        try {
            this->_receiveUdp();
        } catch (std::exception const &e) {
            std::cerr << "ClientNetworkCore::receiveLoop UDP " << e.what() << std::endl;
        }
    }
}

void ClientNetworkCore::quit() noexcept
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
            throw std::runtime_error("ClientNetworkCore::_tramHandler invalid tram type");
    }
}

void ClientNetworkCore::_checkRoom()
{
    if (_roomId == NO_ROOM) {
        throw std::runtime_error("ClientNetworkCore not connected to any room.");
    }
}