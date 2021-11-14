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

#include <cstring>
#include <inttypes.h>
#include <stddef.h>
#include <string>
#include "ISerializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
    using std::string;
    #define ENTITY_TYPE_LEN 10

    class CreateEntityRequest : public Network::ISerializable<CreateEntityRequest> {
      public:
        CreateEntityRequest();
        CreateEntityRequest(uint32_t entityId, string entityType, Time timestamp)
            : entityId(entityId), entityType(), timestamp(timestamp)
        {
            if (entityType.empty()) {
                this->entityType[0] = '\0';
            } else {
                std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
            }
        }

        /**
         * @brief private id of the entity
         */
        uint32_t entityId{0};
        /**
         * @brief type of the entity factory ex: "player", "enemy"
         * @brief a confirmer
         */
        char entityType[ENTITY_TYPE_LEN];
        /**
         * @brief timestamp de creation de l'entité (rollback)
         */
        Time timestamp;

        virtual uint8_t *serialize();
        virtual void deserialize(uint8_t *buffer);
        virtual size_t length() const;
    };

    CreateEntityRequest::CreateEntityRequest()
    {
        this->entityType[0] = '\0';
    }

    uint8_t *CreateEntityRequest::serialize()
    {
        size_t size = sizeof(CreateEntityRequest);
        uint8_t *buffer = new uint8_t[size];

        std::memcpy(buffer, (void *) this, size);
        return buffer;
    }

    void CreateEntityRequest::deserialize(uint8_t *buffer)
    {
        CreateEntityRequest *ptr = reinterpret_cast<CreateEntityRequest *>(buffer);

        this->entityId = ptr->entityId;
        this->entityType = ptr->entityType;
        this->timestamp = ptr->timestamp;
    }

    size_t CreateEntityRequest::length() const
    {
        return sizeof(CreateEntityRequest);
    }
} // namespace Tram

#endif // CREATEENTITYREQUEST_HPP