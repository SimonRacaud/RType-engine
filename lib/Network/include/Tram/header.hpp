/*
** EPITECH PROJECT , 2021
** header
** File description:
** \file header.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef HEADER_HPP
#define HEADER_HPP

#include <stddef.h>

#define MAGIC 4242424242

namespace Tram
{
    enum class TramType {
        GET_ROOM_LIST,
        ROOM_LIST,
        CREATE_ROOM,
        JOIN_ROOM,
        JOIN_ROOM_REPLY,
        QUIT_ROOM,
        CREATE_ENTITY,
        CREATE_ENTITY_REPLY,
        DESTROY_ENTITY,
        SYNC_COMPONENT
    };

    struct header {
        size_t magic{MAGIC};
        size_t size;
        TramType type;
    };
} // namespace Tram

#endif // HEADER_HPP
