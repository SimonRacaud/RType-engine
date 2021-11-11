/*
** EPITECH PROJECT , 2021
** JoinCreateRoomReply
** File description:
** \file JoinCreateRoomReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef JOINCREATEROOMREPLY_HPP
#define JOINCREATEROOMREPLY_HPP

#include <stddef.h>
#include "utils/timeDef.hpp"

namespace Tram {
    struct JoinCreateRoomReply {
        bool accept;
        size_t roomId;
        Time startTimestamp;
    };
}

#endif // JOINCREATEROOMREPLY_HPP