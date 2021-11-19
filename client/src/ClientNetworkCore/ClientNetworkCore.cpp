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
#include "Rollback/ComponentRollback.hpp"
#include "Debug.hpp"

ClientNetworkCore::ClientNetworkCore(Engine::IGameEngine &engine)
try : _engine(engine),
    _tcpClient(shared_ptr<IConnection>(make_shared<AsioClientTCP>())),
    _udpClient(shared_ptr<IConnection>(make_shared<AsioClientUDP>(CLIENT_UDP_PORT)))
{
    this->connect();
} catch (std::exception const &e) {
    std::cerr << "Fatal error ClientNetworkCore::ClientNetworkCore " << e.what() << std::endl;
    exit(84); // TODO TUEZ LEEEE !!! WHAHAHAHAH
}

ClientNetworkCore::~ClientNetworkCore() {}

void ClientNetworkCore::connect()
{
    size_t serverPortTcp = (size_t)GameCore::config->getVar<int>("SERVER_PORT_TCP");
    size_t serverPortUdp = (size_t)GameCore::config->getVar<int>("SERVER_PORT_UDP");
    std::string serverIp = GameCore::config->getVar<std::string>("SERVER_IP");
    bool loop = false;
    size_t count;

    try {
        for (count = 0; !loop && count <= MAX_CONNECT_TRY; count++) {
            loop = this->_tcpClient.connect(serverIp, serverPortTcp);
            loop = loop && this->_udpClient.connect(serverIp, serverPortUdp);
        }
    } catch (std::exception const &e) {
        std::cerr << "ClientNetworkCore::connect " << e.what() << std::endl;
        throw std::runtime_error("ClientNetworkCore::connect Connection failed. Exit.");
    }
    if (count == MAX_CONNECT_TRY) {
        throw std::runtime_error("ClientNetworkCore::connect Connection failed. Exit.");
    }
    PUT_DEBUG("Network connected.");
}


void ClientNetworkCore::getRoomList()
{
    PUT_DEBUG("Send [GetRoomList].");
    try {
        Tram::Serializable tram(Tram::TramType::ROOM_LIST);
        this->_udpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
    SHOW_DEBUG("NETWORK: send get room list");
}

void ClientNetworkCore::createRoom()
{
    PUT_DEBUG("Send [CreateRoom].");
    try {
        Tram::Serializable tram(Tram::TramType::CREATE_ROOM);
        this->_udpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
    SHOW_DEBUG("NETWORK: send create room");
}

void ClientNetworkCore::joinRoom(size_t id)
{
    PUT_DEBUG("Send [JoinRoom] roomId="+to_string(id)+".");
    try {
        Tram::JoinRoom tram(id);
        this->_udpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
}

void ClientNetworkCore::quitRoom()
{
    this->_checkRoom();
    PUT_DEBUG("Send [QuitRoom].");
    try {
        Tram::Serializable tram(Tram::TramType::QUIT_ROOM);
        this->_udpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
    this->_isMaster = false;
}

void ClientNetworkCore::createEntity(Engine::Entity entity, std::string type,
    netVector2f const &position, netVector2f const& velocity)
{
    this->_checkRoom();
    PUT_DEBUG("Send [CreateEntity] entity="+to_string(entity)+", type="+type+".");
    long int timestamp = GET_NOW;
    try {
        Tram::CreateEntityRequest tram(this->_roomId, entity, type, timestamp, position, velocity);
        this->_tcpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
}

void ClientNetworkCore::destroyEntity(Engine::NetworkId id)
{
    this->_checkRoom();
    if (this->isMaster()) {
        PUT_DEBUG("Send [DestroyEntity] networkId="+to_string(id)+".");
        Engine::Entity entityId = this->_engine.getEntityManager().getId(id);

        this->_engine.getEntityManager().remove(entityId);
        try {
            Tram::DestroyEntity tram(this->_roomId, id);
            this->_tcpClient.sendAll(tram);
        } catch (std::runtime_error const &) {
            std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
            GameCore::engine.quit();
        }
    } else {
        throw std::runtime_error("ClientNetworkCore::destroyEntity method called on slave client.");
    }
}

void ClientNetworkCore::syncComponent(Engine::NetworkId id, std::type_index const &componentType,
    size_t componentSize, void *component)
{
    this->_checkRoom();
    PUT_DEBUG("Send [SyncComponent] networkId="+to_string(id)+", componentType="+to_string(componentType.hash_code())
        +", componentName="+to_string(componentType.name()) + ", componentSize="+to_string(componentSize)+".");
    long int timestamp = GET_NOW;
    try {
        Tram::ComponentSync tram(this->_roomId, id, timestamp, componentType, componentSize, component);
        this->_udpClient.sendAll(tram);
    } catch (std::runtime_error const &) {
        std::cerr << "[Info] Server unexpected disconnection. Exit." << std::endl;
        GameCore::engine.quit();
    }
}

void ClientNetworkCore::receiveRoomList(InfoConnection &, Tram::GetRoomList &data)
{
    PUT_DEBUG("Receive [RoomList] nbItem="+to_string(data.nbItem)+".");
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
    PUT_DEBUG("Receive [JoinRoomReply] accept="+to_string(data.accept)+", roomId="+to_string(data.roomId)+
        ", PlayerId="+to_string(data.playerNumber)+".");
    if (data.accept == true) {
        this->_roomId = data.roomId;
        Scene::GameScene *ptr = reinterpret_cast<Scene::GameScene *>(
            (&this->_engine.getSceneManager().get<Scene::GameScene>())
            );
        ptr->setTimeStart(data.startTimestamp); // set game scene countdown
        if (data.playerNumber == 1) {
            this->_isMaster = true;
            PUT_DEBUG("The client is Master.")
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
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    PUT_DEBUG("Receive [CreateEntityReply] accept="+to_string(data.accept)+", entityId="+to_string(data.entityId)
        +", networkId="+to_string(data.networkId)+", entityType="+to_string(data.entityType)+".");
    if (data.accept) {
        this->_engine.getEntityManager().setNetworkId(data.entityId); // apply network id
    } else {
        // rollback entity creation
        this->_engine.getEntityManager().remove(data.entityId);
    }
}

void ClientNetworkCore::receiveCreateEntityRequest(InfoConnection &, Tram::CreateEntityRequest &data)
{
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    PUT_DEBUG("Receive [CreateEntityRequest] id="+to_string(data.id)+", entityType="+to_string(data.entityType)+".");
    // build the entity
    if (this->isMaster()) {
        /// Allocate a new network id, create the asked entity, send reply to the server.
        Engine::NetworkId networkId = GameCore::engine.getEntityManager().getNetworkId();
        data.id = networkId;
        GameCore::entityFactory.build(data);
        Tram::CreateEntityReply tram(data.roomId, true, data.id, networkId, data.ip, data.port,
            data.timestamp, data.entityType, data.position, data.velocity);
    } else {
        /// Execute entity creation order
        GameCore::entityFactory.build(data);
    }
}

void ClientNetworkCore::receiveSyncComponent(InfoConnection &, Tram::ComponentSync &data)
{
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    PUT_DEBUG("Receive [SyncComponent] networkdId="+to_string(data.networkId)+", componentType="+
        to_string(data.componentType)+", componentSize="+to_string(data.componentSize)+".");
    data.component = reinterpret_cast<uint8_t *>(&data) + sizeof(Tram::ComponentSync);
    ComponentRollback::Apply(data); // Apply component on local engine
}

void ClientNetworkCore::receiveDestroyEntity(InfoConnection &, Tram::DestroyEntity &data)
{
    if ((int)data.roomId != this->_roomId) {
        return; // abort
    }
    PUT_DEBUG("Receive [DestroyEntity] networkId="+to_string(data.networkId)+".");
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
    PUT_DEBUG("Quit network core.");
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
    PUT_DEBUG("Receive packet IP="+info.ip+", PORT="+to_string(info.port)+".");
    this->_tramHandler(header, info, buffer);
}

void ClientNetworkCore::_tramHandler(Tram::Serializable &header, InfoConnection &info,
    uint8_t *buffer)
{
    switch (header.type) {
        case Tram::TramType::GET_ROOM_LIST: {
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

