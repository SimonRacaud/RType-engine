/*
** EPITECH PROJECT , 2021
** NetworkRoom
** File description:
** \file NetworkRoom.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef NETWORKROOM_HPP
#define NETWORKROOM_HPP

#include <inttypes.h>
#include <stddef.h>
#include <vector>
#include "InfoConnection.hpp"
#include "Network.hpp"
#include "globalServer.hpp"
#include "utils/timeDef.hpp"

using Network::InfoConnection;

struct NetworkRoom {
    NetworkRoom(NetworkRoom const &self)
    : roomId(self.roomId), startTimestamp(self.startTimestamp), clients(self.clients)
    {}

    NetworkRoom(size_t id, InfoConnection const &master)
        : roomId(id), startTimestamp(GET_NOW + TIME_ROOM_WAIT), masterClient(master)
    {}

    size_t roomId;
    Time startTimestamp;
    /**
     * @brief main client of the game room
     */
    InfoConnection masterClient;
    /**
     * @brief Client's ip + port
     */
    std::vector<InfoConnection> clients;
    /**
     * @brief vector<clients index, network id>
     */
    std::vector<std::tuple<size_t, NetworkId>> clientPlayerNetworkIds;
};

#endif // NETWORKROOM_HPP
