/*
** EPITECH PROJECT , 2021
** ComponentSync
** File description:
** \file ComponentSync.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "Network/Tram/ComponentSync.hpp"
#include "Network/Tram/TramType.hpp"

using namespace Tram;

ComponentSync::ComponentSync() : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync))
{
}

ComponentSync::ComponentSync(size_t roomId, uint32_t networkId, Time timestamp, const std::type_index &componentType,
    size_t componentSize, void *component)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync) + componentSize), roomId(roomId),
      networkId(networkId), timestamp(timestamp), componentType(componentType.hash_code()),
      componentSize(componentSize), component(component)
{
}

ComponentSync::ComponentSync(
    size_t roomId, uint32_t networkId, Time timestamp, size_t componentType, size_t componentSize, void *component)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync) + componentSize), roomId(roomId),
      networkId(networkId), timestamp(timestamp), componentType(componentType), componentSize(componentSize),
      component(component)
{
}

ComponentSync::~ComponentSync()
{
}

uint8_t *ComponentSync::serialize() const
{
    if (this->component == nullptr) {
        throw std::logic_error("ComponentSync::serialize null component");
    }

    uint8_t *buffer = new uint8_t[this->length()];

    std::memset(buffer, 0, this->length());

    std::memcpy(buffer, (uint8_t *) this, sizeof(ComponentSync)); // copy header
    std::memcpy(buffer + sizeof(ComponentSync) /*- sizeof(void *)*/, this->component, this->componentSize); // copy body
    return buffer;
}

void ComponentSync::deserialize(uint8_t *buffer)
{
    if (!buffer)
        throw std::logic_error("ComponentSync::deserialize buffer is null");

    std::memcpy((uint8_t *) this, buffer, sizeof(ComponentSync));
    this->component = new uint8_t[this->componentSize];
    std::memcpy(this->component, buffer + sizeof(ComponentSync), this->componentSize);
}

size_t ComponentSync::length() const
{
    return sizeof(ComponentSync) + this->componentSize;
}

ComponentSync::ComponentSync(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync))
{
    ComponentSync::deserialize(buffer);
}