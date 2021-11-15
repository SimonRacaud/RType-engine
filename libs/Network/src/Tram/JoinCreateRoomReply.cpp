/*
** EPITECH PROJECT, 2021
** JoinCreateRoomReply.cpp
** File description:
** TODO: add description
*/

#include "Tram/JoinCreateRoomReply.hpp"
using namespace Tram;

JoinCreateRoomReply::JoinCreateRoomReply()
    : Tram::Serializable(Tram::TramType::JOIN_ROOM_REPLY, sizeof(JoinCreateRoomReply))
{
}

JoinCreateRoomReply::JoinCreateRoomReply(bool accept, size_t roomId, Time timestamp)
    : Tram::Serializable(Tram::TramType::JOIN_ROOM_REPLY, sizeof(JoinCreateRoomReply)), accept(accept), roomId(roomId),
      startTimestamp(timestamp)
{
}

uint8_t *JoinCreateRoomReply::serialize() const
{
    size_t size = sizeof(JoinCreateRoomReply);
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (void *) this, size);
    return buffer;
}

void JoinCreateRoomReply::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<JoinCreateRoomReply *>(buffer);

    this->roomId = ptr->roomId;
    this->accept = ptr->accept;
    this->startTimestamp = ptr->startTimestamp;
}
size_t JoinCreateRoomReply::length() const
{
    return sizeof(JoinCreateRoomReply);
}
JoinCreateRoomReply::JoinCreateRoomReply(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::JOIN_ROOM_REPLY, sizeof(JoinCreateRoomReply))
{
    JoinCreateRoomReply::deserialize(buffer);
}