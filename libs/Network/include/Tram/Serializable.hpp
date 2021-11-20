/*
** EPITECH PROJECT , 2021
** Serializable
** File description:
** \file Serializable.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef HEADER_HPP
#define HEADER_HPP

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <cstring>
#include "ISerializable.hpp"
#include <unordered_map>

#define MAGIC 4242424242

namespace Tram
{
    enum class TramType {
        NONE,
        GET_ROOM_LIST,  // server
        ROOM_LIST,      // client
        CREATE_ROOM,    // server
        JOIN_ROOM,      // server
        JOIN_ROOM_REPLY, // client
        QUIT_ROOM,      // server
        CREATE_ENTITY_REQUEST,  // client, server
        CREATE_ENTITY_REPLY, // client, server
        DESTROY_ENTITY, // client, server
        SYNC_COMPONENT  // client, server
    };

    const std::unordered_map<TramType, std::string> TramTypeString{{TramType::NONE, "NONE"},
        {TramType::GET_ROOM_LIST, "GET_ROOM_LIST"}, {TramType::ROOM_LIST, "ROOM_LIST"},
        {TramType::CREATE_ROOM, "CREATE_ROOM"}, {TramType::JOIN_ROOM, "JOIN_ROOM"},
        {TramType::JOIN_ROOM_REPLY, "JOIN_ROOM_REPLY"}, {TramType::QUIT_ROOM, "QUIT_ROOM"},
        {TramType::CREATE_ENTITY_REQUEST, "CREATE_ENTITY"}, {TramType::CREATE_ENTITY_REPLY, "CREATE_ENTITY_REPLY"},
        {TramType::DESTROY_ENTITY, "DESTROY_ENTITY"}, {TramType::SYNC_COMPONENT, "SYNC_COMPONENT"}};
    std::ostream &operator<<(std::ostream &stream, const Tram::TramType tram);

    // todo passer à travers tout les types pour init le header
    class Serializable : public Network::ISerializable {
      public:
        explicit Serializable() = default;
        explicit Serializable(TramType type, size_t size = sizeof(Serializable));
        explicit Serializable(uint8_t *data);

        /**
         * @brief magic number to check the data type
         */
        const size_t magic{MAGIC};
        /**
         * @brief Tram total size
         */
        size_t size{sizeof(Serializable)};
        /**
         * @brief Tram type
         */
        TramType type{Tram::TramType::NONE};

        [[nodiscard]] uint8_t *serialize() const override;
        /**
         * @throws InvalidArgument : invalid magic number
         * @param buffer
         */
        void deserialize(uint8_t *buffer) override;
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // HEADER_HPP