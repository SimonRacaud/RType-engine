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
#include "ISerializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
    class JoinCreateRoomReply : public Network::ISerializable {
      public:
        JoinCreateRoomReply() = default;
        JoinCreateRoomReply(bool accept, size_t roomId, Time timestamp);

        bool accept{false};
        size_t roomId{0};
        Time startTimestamp{0};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit JoinCreateRoomReply(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // JOINCREATEROOMREPLY_HPP