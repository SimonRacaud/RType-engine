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
#include <utility>
#include "ISerializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
    using std::string;
    #define ENTITY_TYPE_LEN 10

    class CreateEntityRequest : public Network::ISerializable {
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
        Time timestamp{};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit CreateEntityRequest(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };
} // namespace Tram

#endif // CREATEENTITYREQUEST_HPP