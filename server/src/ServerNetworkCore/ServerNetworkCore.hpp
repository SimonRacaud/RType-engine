/*
** EPITECH PROJECT , 2021
** ServerNetworkCore
** File description:
** \file ServerNetworkCore.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef SERVERNETWORKCORE_HPP
#define SERVERNETWORKCORE_HPP

#include "NetworkRoom.hpp"
#include "global.hpp"
#include "InfoConnection.hpp"
#include "NetworkManager.hpp"
#include "AsioConnectionUDP.hpp"
#include "AsioServerTCP.hpp"
#include "Network.hpp"

#include "Tram/ComponentSync.hpp"
#include "Tram/CreateEntityReply.hpp"
#include "Tram/CreateEntityRequest.hpp"
#include "Tram/DestroyEntity.hpp"
#include "Tram/GetRoomList.hpp"
#include "Tram/JoinCreateRoomReply.hpp"
#include "Tram/JoinRoom.hpp"
#include "Tram/Serializable.hpp"

#include "IServerNetworkCore.hpp"
#include "GarbageEntity/GarbageEntity.hpp"

#include <vector>
#include <memory>
#include <numeric>
#include <algorithm>

using std::vector;
using std::shared_ptr;
using std::make_shared;

using Network::InfoConnection;
using IConnection = Network::IConnection<DataWrapper>;
using AsioServerTCP = Network::AsioServerTCP<DataWrapper>;
using AsioServerUDP = Network::AsioConnectionUDP<DataWrapper>;

// Add that to the config file
#define MAX_ROOM 10
#define MAX_ROOM_CLIENT 4

class ServerNetworkCore : public IServerNetworkCore {
  public:
    ServerNetworkCore();
    virtual ~ServerNetworkCore() = default;

    /**
     * @brief Broadcast entity creation request
     * @param roomId
     * @param id
     * @param type
     */
    void createEntity(size_t roomId, NetworkId id, std::string const &type);
    /**
     * @brief Broadcast entity destruction request
     * @param roomId
     * @param id
     */
    void destroyEntity(size_t roomId, NetworkId id);
    /**
     * @brief Broadcast component synchronization request
     * @param roomId
     * @param id
     * @param componentType
     * @param componentSize
     * @param component
     */
    void syncComponent(size_t roomId, NetworkId id, std::type_index const &componentType,
        size_t componentSize, void *component);

  protected:
    void receiveGetRoomList(InfoConnection &info);
    void receiveCreateRoom(InfoConnection &info);
    void receiveQuitRoom(InfoConnection &info);
    void receiveJoinRoom(InfoConnection &info, Tram::JoinRoom &data);
    void receiveCreateEntityReply(InfoConnection &info, Tram::CreateEntityReply &data);
    void receiveCreateEntityRequest(InfoConnection &info, Tram::CreateEntityRequest &data);
    void receiveDestroyEntity(InfoConnection &info, Tram::DestroyEntity &data);
    void receiveSyncComponent(InfoConnection &info, Tram::ComponentSync &data);

    void receiveLoop();

  private:
    void _receiveFromChannel(NetworkManager &net);
    void _tramHandler(Tram::Serializable &header, InfoConnection &info,
        uint8_t *buffer);

    shared_ptr<NetworkRoom> _getRoom(size_t roomId);

    void _removePlayer(shared_ptr<NetworkRoom> &room, size_t clientIndex);

  private:
    NetworkManager _tcpServer;
    NetworkManager _udpServer;
    GarbageEntity _garbageEntity;
    bool _loop{true};
    vector<shared_ptr<NetworkRoom>> _rooms;
    vector<size_t> _roomFreeIds;
};

#endif // SERVERNETWORKCORE_HPP
