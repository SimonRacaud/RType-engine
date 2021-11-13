/*
** EPITECH PROJECT , 2021
** DestroyEntity
** File description:
** \file DestroyEntity.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef DESTROYENTITY_HPP
#define DESTROYENTITY_HPP

#include <cstring>
#include <inttypes.h>
#include <stddef.h>
#include "ISerializable.hpp"

namespace Tram
{
    class DestroyEntity : public Network::ISerializable {
      public:
        DestroyEntity() = default;
        DestroyEntity(uint32_t networkId) : networkId(networkId)
        {
        }
        /**
         * @brief Network id of the entity
         */
        uint32_t networkId{0};

        virtual uint8_t *serialize();
        virtual void deserialize(uint8_t *buffer);
        virtual size_t length() const;
    };

    uint8_t *DestroyEntity::serialize()
    {
        size_t size = this->length();
        uint8_t *buffer = new uint8_t[size];

        std::memcpy(buffer, (void *) this, size);
        return buffer;
    }

    void DestroyEntity::deserialize(uint8_t *buffer)
    {
        DestroyEntity *ptr = reinterpret_cast<DestroyEntity *>(buffer);

        this->networkId = ptr->networkId;
    }

    size_t DestroyEntity::length() const
    {
        return sizeof(DestroyEntity);
    }
} // namespace Tram

#endif // DESTROYENTITY_HPP