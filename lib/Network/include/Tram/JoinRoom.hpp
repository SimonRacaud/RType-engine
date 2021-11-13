/*
** EPITECH PROJECT , 2021
** JoinRoomReply
** File description:
** \file JoinRoomReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef JOINROOMREPLY_HPP
#define JOINROOMREPLY_HPP

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <string>
#include "ISerializable.hpp"

namespace Tram
{
    class JoinRoom : public Network::ISerializable {
      public:
        JoinRoom() = default;
        explicit JoinRoom(size_t roomId) : roomId(roomId){};
        explicit JoinRoom(uint8_t *buffer);

        size_t roomId{0};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // JOINROOMREPLY_HPP