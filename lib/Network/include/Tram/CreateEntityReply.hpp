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

#include <cstring>
#include <inttypes.h>
#include <stddef.h>
#include "ISerializable.hpp"

namespace Tram
{
    class CreateEntityReply : public Network::ISerializable<CreateEntityReply> {
      public:
        CreateEntityReply() = default;
        CreateEntityReply(bool accept, uint32_t entityId, uint32_t networkId)
            : accept(accept), entityId(entityId), networkId(networkId)
        {
        }
        explicit CreateEntityReply(uint8_t *buffer);
        //        CreateEntityReply(CreateEntityReply &rhs);
        //        CreateEntityReply(CreateEntityReply &&rhs) noexcept;
        /**
         * @brief if the request was accepted
         */
        bool accept{false};
        /**
         * @brief private id of the local entity
         */
        uint32_t entityId{0};
        /**
         * @brief new network id of the entity
         */
        uint32_t networkId{0};

        virtual uint8_t *serialize();
        static uint8_t *serialize(CreateEntityReply &toSerialize);
        virtual void deserialize(uint8_t *buffer);
        virtual size_t length() const;
    };
} // namespace Tram

#endif // CREATEENTITYREPLY_HPP