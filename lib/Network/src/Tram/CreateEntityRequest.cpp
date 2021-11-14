/*
** EPITECH PROJECT, 2021
** CreateEntityRequest.cpp
** File description:
** TODO: add description
*/

#include "Tram/CreateEntityRequest.hpp"

using namespace Tram;

CreateEntityRequest::CreateEntityRequest()
{
    this->entityType[0] = '\0';
}

uint8_t *CreateEntityRequest::serialize() const
{
    size_t size = sizeof(CreateEntityRequest);
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (void *) this, size);
    return buffer;
}

void CreateEntityRequest::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityRequest *>(buffer);

    this->entityId = ptr->entityId;
    this->entityType = ptr->entityType;
    this->timestamp = ptr->timestamp;
}

size_t CreateEntityRequest::length() const
{
    return sizeof(CreateEntityRequest);
}
CreateEntityRequest::CreateEntityRequest(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityRequest *>(buffer);

    this->entityId = ptr->entityId;
    this->entityType = ptr->entityType;
    this->timestamp = ptr->timestamp;
}