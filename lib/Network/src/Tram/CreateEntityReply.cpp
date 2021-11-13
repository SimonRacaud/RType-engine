/*
** EPITECH PROJECT , 2021
** CreateEntityReply
** File description:
** \file CreateEntityReply.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "Tram/CreateEntityReply.hpp"
#include <utility>

using namespace Tram;

uint8_t *CreateEntityReply::serialize()
{
    size_t size = sizeof(CreateEntityReply);
    uint8_t *buffer = new uint8_t[size];

    std::memcpy(buffer, this, size);
    return buffer;
}

void CreateEntityReply::deserialize(uint8_t *buffer)
{
    CreateEntityReply *ptr = reinterpret_cast<CreateEntityReply *>(buffer);

    this->accept = ptr->accept;
    this->entityId = ptr->entityId;
    this->networkId = ptr->networkId;
}

size_t CreateEntityReply::length() const
{
    return sizeof(CreateEntityReply);
}
CreateEntityReply::CreateEntityReply(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityReply *>(buffer);

    this->accept = ptr->accept;
    this->entityId = ptr->entityId;
    this->networkId = ptr->networkId;
}
uint8_t *CreateEntityReply::serialize(CreateEntityReply &toSerialize)
{
    size_t size = sizeof(CreateEntityReply);
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (void *) &toSerialize, size);
    return buffer;
}
/*
 CreateEntityReply::CreateEntityReply(CreateEntityReply &&rhs) noexcept
 {
     this->accept = std::forward<size_t>(rhs.accept);
     this->entityId = std::forward<uint32_t>(rhs.entityId);
     this->networkId = std::forward<uint32_t>(rhs.networkId);
     //    rhs.accept = false;
     //    rhs.entityId = 0;
     //    rhs.networkId = 0;
 }
 CreateEntityReply::CreateEntityReply(CreateEntityReply &rhs)
 {
     this->accept = rhs.accept;
     this->entityId = rhs.entityId;
     this->networkId = rhs.networkId;
 }*/