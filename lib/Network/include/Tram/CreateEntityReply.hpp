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

namespace Tram
{
    class CreateEntityReply : public Tram::Serializable {
      public:
        CreateEntityReply();
        CreateEntityReply(size_t roomId, bool accept, uint32_t entityId, uint32_t networkId);

        size_t roomId{0};
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

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit CreateEntityReply(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };
} // namespace Tram

#endif // CREATEENTITYREPLY_HPP