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
#include "ISerializable.hpp"

#define MAGIC 4242424242

namespace Tram
{
    enum class TramType {
        NONE,
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

    // todo passer à travers tout les types pour init le header
    class Serializable : public Network::ISerializable {
      public:
        explicit Serializable() = default;
        explicit Serializable(TramType type, size_t size = 0);
        explicit Serializable(uint8_t *data);

        /**
         * @brief magic number to check the data type
         */
        const size_t magic{MAGIC};
        /**
         * @brief Tram total size
         */
        size_t size{0};
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