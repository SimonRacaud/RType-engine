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

#include <stddef.h>
#include <vector>
#include "utils/timeDef.hpp"
#include "InfoConnection.hpp"
#include "Network.hpp"

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
    InfoConnection masterClient;
    std::vector<InfoConnection> clients;
};

#endif // NETWORKROOM_HPP
