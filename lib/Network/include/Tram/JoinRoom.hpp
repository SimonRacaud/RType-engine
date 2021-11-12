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

#include <inttypes.h>
#include <stddef.h>
#include <string>
#include <cstring>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        class JoinRoom : public ISerializable<JoinRoom> {
          public:
            JoinRoom(size_t roomId) : roomId(roomId) {};

            size_t roomId;

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
            virtual size_t length() const;
        };

        uint8_t *JoinRoom::deserialize()
        {
            size_t size = sizeof(JoinRoom);
            uint8_t *buffer = new uint8_t[size];

            std::memcpy(buffer, (void*)this, size);
            return buffer;
        }

        void JoinRoom::serialize(uint8_t *buffer)
        {
            JoinRoom *ptr = reinterpret_cast<JoinRoom *>(buffer);

            this->roomId = ptr->roomId;
        }

        size_t JoinRoom::length() const
        {
            return sizeof(JoinRoom);
        }
    } // namespace Tram
}

#endif // JOINROOMREPLY_HPP