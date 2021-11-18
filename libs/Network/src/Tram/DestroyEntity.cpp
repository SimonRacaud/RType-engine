/*
** EPITECH PROJECT, 2021
** DestroyEntity.cpp
** File description:
** TODO: add description
*/

#include "Tram/DestroyEntity.hpp"

using namespace Tram;

DestroyEntity::DestroyEntity() : Tram::Serializable(Tram::TramType::DESTROY_ENTITY, sizeof(DestroyEntity))
{
}

DestroyEntity::DestroyEntity(size_t roomId, uint32_t networkId)
    : Tram::Serializable(Tram::TramType::DESTROY_ENTITY, sizeof(DestroyEntity)), roomId(roomId), networkId(networkId)
{
}

uint8_t *DestroyEntity::serialize() const
{
    size_t len = this->length();
    auto *buffer = new uint8_t[len];

    std::memcpy(buffer, (void *) this, len);
    return buffer;
}
void DestroyEntity::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<DestroyEntity *>(buffer);

    this->size = ptr->size;
    this->type = ptr->type;
    // body
    this->roomId = ptr->roomId;
    this->networkId = ptr->networkId;
}

size_t DestroyEntity::length() const
{
    return sizeof(DestroyEntity);
}

DestroyEntity::DestroyEntity(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::DESTROY_ENTITY, sizeof(DestroyEntity))
{
    DestroyEntity::deserialize(buffer);
}