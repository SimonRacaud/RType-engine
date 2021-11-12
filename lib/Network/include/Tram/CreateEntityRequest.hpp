/*
** EPITECH PROJECT , 2021
** CreateEntityRequest
** File description:
** \file CreateEntityRequest.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef CREATEENTITYREQUEST_HPP
#define CREATEENTITYREQUEST_HPP

#include <inttypes.h>
#include <stddef.h>
#include <string>
#include <cstring>
#include "ISerializable.hpp"
#include "utils/timeDef.hpp"

namespace Network
{
    namespace Tram
    {
        using std::string;

        class CreateEntityRequest : public ISerializable<CreateEntityRequest> {
          public:
            CreateEntityRequest(uint32_t entityId, string entityType, Time timestamp)
                : entityId(entityId), entityType(entityType), timestamp(timestamp) {}

            /**
             * @brief private id of the entity
             */
            uint32_t entityId;
            /**
             * @brief type of the entity factory ex: "player", "enemy"
             * @brief a confirmer
             */
            string entityType;
            /**
             * @brief timestamp de creation de l'entité (rollback)
             */
            Time timestamp;

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
        };

        uint8_t *CreateEntityRequest::deserialize()
        {
            size_t size = sizeof(CreateEntityRequest);
            uint8_t *buffer = new uint8_t[size];

            std::memcpy(buffer, (void*)this, size);
            return buffer;
        }

        void CreateEntityRequest::serialize(uint8_t *buffer)
        {
            CreateEntityRequest *ptr = reinterpret_cast<CreateEntityRequest *>(buffer);

            this->entityId = ptr->entityId;
            this->entityType = ptr->entityType;
            this->timestamp = ptr->timestamp;
        }
    } // namespace Tram
}

#endif // CREATEENTITYREQUEST_HPP