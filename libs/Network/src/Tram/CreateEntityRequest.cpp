/*
** EPITECH PROJECT, 2021
** CreateEntityRequest.cpp
** File description:
** TODO: add description
*/

#include "Tram/CreateEntityRequest.hpp"

using namespace Tram;

CreateEntityRequest::CreateEntityRequest()
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REQUEST, sizeof(CreateEntityRequest))
{
    entityType[0] = '\0';
    ip[0] = '\0';
}

CreateEntityRequest::CreateEntityRequest(size_t roomId, uint32_t id, string entityType,
    Time timestamp, netVector2f const& position, netVector2f const& velocity)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REQUEST, sizeof(CreateEntityRequest)),
      roomId(roomId),
      id(id),
      timestamp(timestamp),
      port(0),
      position(position),
      velocity(velocity)
{
    if (entityType.empty()) {
        this->entityType[0] = '\0';
    } else {
        std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
    }
    this->ip[0] = '\0';
}

CreateEntityRequest::CreateEntityRequest(size_t roomId, uint32_t id, string entityType, Time timestamp,
    size_t port, std::string const &ip, netVector2f const& position, netVector2f const& velocity)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REQUEST, sizeof(CreateEntityRequest)),
      roomId(roomId),
      id(id),
      timestamp(timestamp),
      port(port),
      position(position),
      velocity(velocity)
{
    if (entityType.empty()) {
        this->entityType[0] = '\0';
    } else {
        std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
    }
    std::strncpy(this->ip, ip.c_str(), IP_LENGTH - 1);
}

CreateEntityRequest::CreateEntityRequest(size_t roomId, string entityType, Time timestamp, netVector2f const& position,
    netVector2f const& velocity)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REQUEST, sizeof(CreateEntityRequest)),
      roomId(roomId),
      id(-1),
      timestamp(timestamp),
      port(0),
      position(position),
      velocity(velocity)
{
    this->ip[0] = '\0';
    if (entityType.empty()) {
        this->entityType[0] = '\0';
    } else {
        std::strncpy(this->entityType, entityType.c_str(), ENTITY_TYPE_LEN - 1);
    }
}

uint8_t *CreateEntityRequest::serialize() const
{
    size_t len = this->length();
    auto *buffer = new uint8_t[len];

    std::memset(buffer, 0, len);
    std::memcpy(buffer, (void *) this, len);
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
    this->id = ptr->id;
    std::strcpy(this->entityType, ptr->entityType);
    this->timestamp = ptr->timestamp;
    this->port = ptr->port;
    this->position = ptr->position;
    this->velocity = ptr->velocity;
    std::strcpy(this->ip, ptr->ip);
}

size_t CreateEntityRequest::length() const
{
    return sizeof(CreateEntityRequest);
}

CreateEntityRequest::CreateEntityRequest(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REQUEST, sizeof(CreateEntityRequest))

{
    CreateEntityRequest::deserialize(buffer);
}