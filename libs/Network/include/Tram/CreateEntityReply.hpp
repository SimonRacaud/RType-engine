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

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include "Tram/Serializable.hpp"
#include "utils/timeDef.hpp"
#include "utils/netVector2f.hpp"

namespace Tram
{
    #ifndef IP_LENGTH
        #define IP_LENGTH 129
    #endif
    #ifndef ENTITY_TYPE_LEN
        #define ENTITY_TYPE_LEN 20
    #endif
    using Network::netVector2f;

    class CreateEntityReply : public Tram::Serializable {
      public:
        CreateEntityReply();
        // client master -> server
        CreateEntityReply(size_t roomId, bool accept, uint32_t networkId, std::string const &ip,
            size_t port, Time timestamp, std::string const &entityType, netVector2f const& position,
            netVector2f const& velocity);
        // client master -> server -> client slave
        CreateEntityReply(size_t roomId, bool accept, int64_t entityId, uint32_t networkId, std::string const &ip,
            size_t port, Time timestamp, std::string const &entityType, netVector2f const& position,
            netVector2f const& velocity);

        size_t roomId{0};
        /**
         * @brief if the request was accepted
         */
        bool accept{false};
        /**
         * @brief private id of the local entity (slave client -> server or server -> client)
         * @brief If == -1 : the request came from the server. (master client -> server)
         */
        int64_t entityId{0};
        /**
         * @brief new network id of the entity
         */
        uint32_t networkId{0};
        /**
         * @brief timestamp de creation de l'entité (rollback)
         */
        Time timestamp{};
        /**
         * @brief entity init position
         */
        Network::netVector2f position;
        /**
         * @brief entity init velocity
         */
        Network::netVector2f velocity;
        /**
         * @brief emitter client ip + post (slave client -> server -> master client)
         */
        size_t port{0};
        char ip[IP_LENGTH]{0};
        /**
         * @brief type of the entity factory ex: "player", "enemy"
         */
        char entityType[ENTITY_TYPE_LEN]{0};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit CreateEntityReply(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };
} // namespace Tram

#endif // CREATEENTITYREPLY_HPP