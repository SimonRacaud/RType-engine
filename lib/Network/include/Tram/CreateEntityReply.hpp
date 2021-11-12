/*
** EPITECH PROJECT , 2021
** CreateEntityReply
** File description:
** \file CreateEntityReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef CREATEENTITYREPLY_HPP
#define CREATEENTITYREPLY_HPP

#include <inttypes.h>
#include <stddef.h>
#include <cstring>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        class CreateEntityReply : public ISerializable<CreateEntityReply> {
          public:
            CreateEntityReply(bool accept, uint32_t entityId, uint32_t networkId)
                : accept(accept), entityId(entityId), networkId(networkId) {}
            /**
             * @brief if the request was accepted
             */
            bool accept;
            /**
             * @brief private id of the local entity
             */
            uint32_t entityId;
            /**
             * @brief new network id of the entity
             */
            uint32_t networkId;

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
        };
    }
}

#endif // CREATEENTITYREPLY_HPP
