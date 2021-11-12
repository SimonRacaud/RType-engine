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

#include <inttypes.h>
#include <stddef.h>
#include <cstring>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        class DestroyEntity : public ISerializable<DestroyEntity> {
          public:
            DestroyEntity(uint32_t networkId) : networkId(networkId) {}
            /**
             * @brief Network id of the entity
             */
            uint32_t networkId;

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
        };

        uint8_t *DestroyEntity::deserialize()
        {
            size_t size = sizeof(DestroyEntity);
            uint8_t *buffer = new uint8_t[size];

            std::memcpy(buffer, (void*)this, size);
            return buffer;
        }

        void DestroyEntity::serialize(uint8_t *buffer)
        {
            DestroyEntity *ptr = reinterpret_cast<DestroyEntity *>(buffer);

            this->networkId = ptr->networkId;
        }
    }
}

#endif // DESTROYENTITY_HPP
