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

using namespace Network::Tram;

uint8_t *CreateEntityReply::deserialize()
{
    size_t size = sizeof(CreateEntityReply);
    uint8_t *buffer = new uint8_t[size];

    std::memcpy(buffer, this, size);
    return buffer;
}

void CreateEntityReply::serialize(uint8_t *buffer)
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