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

#include <cstring>
#include <inttypes.h>
#include <stddef.h>
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

    //    std::unordered_map<TramType, >

    class header : public Network::ISerializable<TramType> {
      public:
        header(TramType type, size_t size = 0);
        explicit header(uint8_t *data);

        /**
         * @brief magic number to check the data type
         */
        size_t magic{MAGIC};
        /**
         * @brief Tram total size
         */
        size_t size{0};
        /**
         * @brief Tram type
         */
        TramType type;

        uint8_t *serialize() override;
        /**
         * @throws InvalidArgument : invalid magic number
         * @param buffer
         */
        void deserialize(uint8_t *buffer) override;
        [[nodiscard]] size_t length() const override;
    };

    header::header(TramType type, size_t size) : size(size), type(type)
    {
    }

    uint8_t *header::serialize()
    {
        size_t length = this->length();
        auto *buffer = new uint8_t[length];

        std::memcpy(buffer, (void *) this, length);
        return buffer;
    }

    void header::deserialize(uint8_t *buffer)
    {
        auto *ptr = reinterpret_cast<header *>(buffer);

        if (this->magic != ptr->magic) {
            throw std::invalid_argument("header::deserialize invalid magic number");
        }
        this->size = ptr->size;
        this->type = ptr->type;
    }

    size_t header::length() const
    {
        return sizeof(header);
    }
    header::header(uint8_t *data)
    {
        auto *ptr = reinterpret_cast<header *>(data);

        if (this->magic != ptr->magic) {
            throw std::invalid_argument("header::deserialize invalid magic number");
        }
        this->size = ptr->size;
        this->type = ptr->type;
    }
} // namespace Tram

#endif // HEADER_HPP