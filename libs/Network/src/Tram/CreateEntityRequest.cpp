/*
** EPITECH PROJECT, 2021
** CreateEntityRequest.cpp
** File description:
** TODO: add description
*/

#include "Tram/CreateEntityRequest.hpp"

using namespace Tram;

CreateEntityRequest::CreateEntityRequest()
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY, sizeof(CreateEntityRequest))
{
    entityType[0] = '\0';
}
CreateEntityRequest::CreateEntityRequest(size_t roomId, uint32_t entityId, string entityType, Time timestamp)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY, sizeof(CreateEntityRequest)), roomId(roomId), entityId(entityId),
      timestamp(timestamp)
{
    if (entityType.empty()) {
        this->entityType[0] = '\0';
    } else {
        std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
    }
}

uint8_t *CreateEntityRequest::serialize() const
{
    size_t size = this->length();
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (void *) this, size);
    return buffer;
}

void CreateEntityRequest::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityRequest *>(buffer);

    // header
    this->size = ptr->size;
    this->type = ptr->type;
    // body
    this->roomId = ptr->roomId;
    this->entityId = ptr->entityId;
    std::strcpy(this->entityType, ptr->entityType);
    this->timestamp = ptr->timestamp;
}

size_t CreateEntityRequest::length() const
{
    return sizeof(CreateEntityRequest);
}

CreateEntityRequest::CreateEntityRequest(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY, sizeof(CreateEntityRequest))

{
    CreateEntityRequest::deserialize(buffer);
}