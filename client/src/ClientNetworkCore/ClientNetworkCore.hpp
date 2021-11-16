/*
** EPITECH PROJECT , 2021
** ClientNetworkCore
** File description:
** \file ClientNetworkCore.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef CLIENTNETWORKCORE_HPP
#define CLIENTNETWORKCORE_HPP

#include "InfoConnection.hpp"
#include "NetworkManager.hpp"
#include "AsioClientTCP.hpp"
#include "AsioConnectionUDP.hpp"
#include "EngineCore.hpp"
#include "Tram/ComponentSync.hpp"
#include "Tram/CreateEntityReply.hpp"
#include "Tram/CreateEntityRequest.hpp"
#include "Tram/DestroyEntity.hpp"
#include "Tram/GetRoomList.hpp"
#include "Tram/JoinCreateRoomReply.hpp"
#include "Tram/JoinRoom.hpp"
#include "Tram/Serializable.hpp"
#include "GameCore/GameCore.hpp"

#include "Network.hpp"

#define NO_ROOM -1

using Network::InfoConnection;
using IConnection = Network::IConnection<DataWrapper>;
using AsioClientTCP = Network::AsioClientTCP<DataWrapper>;
using AsioClientUDP = Network::AsioConnectionUDP<DataWrapper>;

using std::to_string;
using std::shared_ptr;
using std::make_shared;

class ClientNetworkCore {
  public:
    ClientNetworkCore(Engine::IGameEngine &engine);
    virtual ~ClientNetworkCore();

    void getRoomList();
    void createRoom();
    void joinRoom(size_t id);
    void quitRoom();
    void createEntity(Engine::Entity entity, std::string type);
    void destroyEntity(Engine::NetworkId id);
    void syncComponent(Engine::NetworkId id, std::type_index const &componentType, size_t componentSize,
        void *component);

    /**
     * @brief Stop receive loop
     */
    void quit() noexcept;

  protected:
    void receiveRoomList(InfoConnection &info, Tram::GetRoomList &data);
    void receiveJoinRoomReply(InfoConnection &info, Tram::JoinCreateRoomReply &data);
    void receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data);
    void receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data);
    void receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data);
    void receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data);

    void receiveLoop();

  private:
    void _receiveTcp();
    void _receiveUdp();
    void _tramExtractor(uint8_t *buffer, std::pair<std::string, std::size_t> &client);
    void _tramHandler(Tram::Serializable &header, InfoConnection &info, uint8_t *buffer);

    void _checkRoom();

  private:
    Engine::IGameEngine &_engine;
    NetworkManager _tcpClient;
    NetworkManager _udpClient;
    bool _loop{true};
    int _roomId{NO_ROOM};
};

#endif // CLIENTNETWORKCORE_HPP
