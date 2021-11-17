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

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <string>
#include <utility>
#include "Tram/Serializable.hpp"
#include "utils/timeDef.hpp"
#include "utils/netVector2f.hpp"

namespace Tram
{
    using std::string;

    #ifndef ENTITY_TYPE_LEN
        #define ENTITY_TYPE_LEN 10
    #endif
    #ifndef IP_LENGTH
        #define IP_LENGTH 129
    #endif

    using Network::netVector2f;

    class CreateEntityRequest : public Serializable {
      public:
        CreateEntityRequest();
        // slave client -> server |or| server -> slave clients |or| master client -> server
        CreateEntityRequest(size_t roomId, uint32_t id, string entityType, Time timestamp, netVector2f const& position,
            netVector2f const& velocity);
        // (slave client ->) server -> master client
        CreateEntityRequest(size_t roomId, uint32_t id, string entityType, Time timestamp,
            size_t port, std::string const &ip, netVector2f const& position,
            netVector2f const& velocity);
        // server -> master client
        CreateEntityRequest(size_t roomId, string entityType, Time timestamp, netVector2f const& position,
            netVector2f const& velocity);

        size_t roomId{0};
        /**
         * @brief private id of the entity (slave client -> server)
         * @brief network id of the entity (server -> slave client or master client -> server)
         * @brief -1 if (server -> master client)
         */
        int64_t id{-1};
        /**
         * @brief timestamp de creation de l'entité (rollback)
         */
        Time timestamp{};
        /**
         * @brief emitter client ip + post (slave client -> server -> master client)
         */
        size_t port{0};
        /**
         * @brief entity init position
         */
        Network::netVector2f position;
        /**
         * @brief entity init velocity
         */
        Network::netVector2f velocity;
        /**
         * @brief type of the entity factory ex: "player", "enemy"
         */
        char entityType[ENTITY_TYPE_LEN]{0};
        /**
         * \brief emitter client ip + post (slave client -> server -> master client)
         */
        char ip[IP_LENGTH]{0};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit CreateEntityRequest(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };
} // namespace Tram

#endif // CREATEENTITYREQUEST_HPP