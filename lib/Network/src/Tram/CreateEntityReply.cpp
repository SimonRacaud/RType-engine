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

using namespace Tram;

CreateEntityReply::CreateEntityReply()
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply))
{
}

CreateEntityReply::CreateEntityReply(bool accept, uint32_t entityId, uint32_t networkId)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply)), accept(accept),
      entityId(entityId), networkId(networkId)
{
}

uint8_t *CreateEntityReply::serialize() const
{
    size_t size = sizeof(CreateEntityReply);
    auto *buffer = new uint8_t[size];

    std::memcpy(buffer, (uint8_t *) this, size);
    return buffer;
}

void CreateEntityReply::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<CreateEntityReply *>(buffer);

    this->accept = ptr->accept;
    this->entityId = ptr->entityId;
    this->networkId = ptr->networkId;
}

size_t CreateEntityReply::length() const
{
    return sizeof(CreateEntityReply);
}
CreateEntityReply::CreateEntityReply(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(CreateEntityReply))
{
    auto *ptr = reinterpret_cast<CreateEntityReply *>(buffer);

    this->accept = ptr->accept;
    this->entityId = ptr->entityId;
    this->networkId = ptr->networkId;
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