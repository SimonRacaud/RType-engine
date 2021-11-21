/*
** EPITECH PROJECT, 2021
** TramType.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_SERVER_TRAMTYPE_HPP
#define R_TYPE_SERVER_TRAMTYPE_HPP

#include <unordered_map>

namespace Tram
{
    enum class TramType {
        NONE,
        GET_ROOM_LIST,         // server
        ROOM_LIST,             // client
        CREATE_ROOM,           // server
        JOIN_ROOM,             // server
        JOIN_ROOM_REPLY,       // client
        QUIT_ROOM,             // server
        CREATE_ENTITY_REQUEST, // client, server
        CREATE_ENTITY_REPLY,   // client, server
        DESTROY_ENTITY,        // client, server
        SYNC_COMPONENT,        // client, server
        END_GAME,
    };

    const std::unordered_map<TramType, std::string> TramTypeString{{TramType::NONE, "NONE"},
        {TramType::GET_ROOM_LIST, "GET_ROOM_LIST"}, {TramType::ROOM_LIST, "ROOM_LIST"},
        {TramType::CREATE_ROOM, "CREATE_ROOM"}, {TramType::JOIN_ROOM, "JOIN_ROOM"},
        {TramType::JOIN_ROOM_REPLY, "JOIN_ROOM_REPLY"}, {TramType::QUIT_ROOM, "QUIT_ROOM"},
        {TramType::CREATE_ENTITY_REQUEST, "CREATE_ENTITY"}, {TramType::CREATE_ENTITY_REPLY, "CREATE_ENTITY_REPLY"},
        {TramType::DESTROY_ENTITY, "DESTROY_ENTITY"}, {TramType::SYNC_COMPONENT, "SYNC_COMPONENT"},
        {TramType::END_GAME, "END_GAME"}};
    std::ostream &operator<<(std::ostream &stream, Tram::TramType tram);

} // namespace Tram

#endif // R_TYPE_SERVER_TRAMTYPE_HPP