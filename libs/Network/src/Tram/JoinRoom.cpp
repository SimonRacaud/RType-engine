/*
** EPITECH PROJECT, 2021
** JoinRoom.cpp
** File description:
** TODO: add description
*/

#include "Tram/JoinRoom.hpp"

using namespace Tram;

JoinRoom::JoinRoom() : Tram::Serializable(Tram::TramType::JOIN_ROOM, sizeof(JoinRoom))
{
}

JoinRoom::JoinRoom(size_t roomId) : Tram::Serializable(Tram::TramType::JOIN_ROOM, sizeof(JoinRoom)), roomId(roomId)
{
}

uint8_t *JoinRoom::serialize() const
{
    size_t size = sizeof(JoinRoom);
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (void *) this, size);
    return buffer;
}

void JoinRoom::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<JoinRoom *>(buffer);

    this->roomId = ptr->roomId;
}

size_t JoinRoom::length() const
{
    return sizeof(JoinRoom);
}

JoinRoom::JoinRoom(uint8_t *buffer) : Tram::Serializable(Tram::TramType::JOIN_ROOM, sizeof(JoinRoom))
{
    JoinRoom::deserialize(buffer);
}