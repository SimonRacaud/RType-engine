/*
** EPITECH PROJECT , 2021
** JoinCreateRoomReply
** File description:
** \file JoinCreateRoomReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef JOINCREATEROOMREPLY_HPP
#define JOINCREATEROOMREPLY_HPP

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <string>
#include "Network/Serializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
    class JoinCreateRoomReply : public Tram::Serializable {
      public:
        JoinCreateRoomReply();
        JoinCreateRoomReply(bool accept, size_t roomId = 0, Time timestamp = 0, int playerNumber = -1);

        /**
         * @brief If the connection is accepted
         */
        bool accept{false};
        /**
         * @brief The room id
         */
        size_t roomId{0};
        /**
         * @brief The moment the game will start.
         */
        Time startTimestamp{0};
        /**
         * @brief The player id [0-3] (for the skin color)
         */
        int playerNumber{-1};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit JoinCreateRoomReply(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // JOINCREATEROOMREPLY_HPP