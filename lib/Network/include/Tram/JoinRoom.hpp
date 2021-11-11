/*
** EPITECH PROJECT , 2021
** JoinRoomReply
** File description:
** \file JoinRoomReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef JOINROOMREPLY_HPP
#define JOINROOMREPLY_HPP

#include <stddef.h>

namespace Tram
{
    struct JoinRoom {
        size_t roomId;
        static inline std::size_t size()
        {
            return sizeof(JoinRoom);
        }
    };
} // namespace Tram

#endif // JOINROOMREPLY_HPP