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
        class JoinCreateRoomReply : public ISerializable<JoinCreateRoomReply> {
          public:
            JoinCreateRoomReply() = default;
            JoinCreateRoomReply(bool accept, size_t roomId, Time timestamp);

            bool accept{false};
            size_t roomId{0};
            Time startTimestamp{0};

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
            virtual size_t length() const;
        };

        JoinCreateRoomReply::JoinCreateRoomReply(bool accept, size_t roomId, Time timestamp)
        : accept(accept), roomId(roomId), startTimestamp(timestamp)
        {}

        uint8_t *JoinCreateRoomReply::deserialize()
        {
            size_t size = sizeof(JoinCreateRoomReply);
            uint8_t *buffer = new uint8_t[size];

            std::memcpy(buffer, (void*)this, size);
            return buffer;
        }

        void JoinCreateRoomReply::serialize(uint8_t *buffer)
        {
            JoinCreateRoomReply *ptr = reinterpret_cast<JoinCreateRoomReply *>(buffer);

            this->roomId = ptr->roomId;
            this->accept = ptr->accept;
            this->startTimestamp = ptr->startTimestamp;
        }

        size_t JoinCreateRoomReply::length() const
        {
            return sizeof(JoinCreateRoomReply);
        }
    }
}

#endif // JOINCREATEROOMREPLY_HPP