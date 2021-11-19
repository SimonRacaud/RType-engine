/*
** EPITECH PROJECT , 2021
** ComponentSync
** File description:
** \file ComponentSync.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "Tram/ComponentSync.hpp"

using namespace Tram;

ComponentSync::ComponentSync() : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync))
{
}

ComponentSync::ComponentSync(size_t roomId, uint32_t networkId, Time timestamp, const std::type_index &componentType,
    size_t componentSize, void *component)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync) + componentSize),
      roomId(roomId),
      networkId(networkId),
      timestamp(timestamp),
      componentType(componentType.hash_code()),
      componentSize(componentSize),
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
    auto *buffer = new uint8_t[this->length() + this->componentSize];
    std::memset(buffer, 0, this->length() + this->componentSize);
    auto ptr = reinterpret_cast<ComponentSync *>(buffer);

    std::memcpy(buffer, (uint8_t *) this, sizeof(ComponentSync));         // copy header
    ptr->component = static_cast<void *>(buffer + sizeof(ComponentSync)); // update header ptr
    std::memcpy(ptr->component, this->component, this->componentSize);    // copy body
    return buffer;
}

void ComponentSync::deserialize(uint8_t *buffer)
{
    auto ptr = reinterpret_cast<ComponentSync *>(buffer);

    *this = *ptr;
}

ComponentSync &ComponentSync::operator=(const ComponentSync &other)
{
    // copy header
    this->size = other.size;
    this->type = other.type;
    // copy body
    this->roomId = other.roomId;
    this->networkId = other.networkId;
    this->timestamp = other.timestamp;
    this->componentType = other.componentType;
    this->componentSize = other.componentSize;
    if (other.component == nullptr) {
        this->component = nullptr;
    } else {
        this->component = new uint8_t[this->componentSize];                 // alloc body
        std::memcpy(this->component, other.component, this->componentSize); // copy body
    }
    return *this;
}

size_t ComponentSync::length() const
{
    return sizeof(ComponentSync) + this->componentSize;
}

ComponentSync::ComponentSync(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync))
{
    auto *ptr = reinterpret_cast<ComponentSync *>(buffer);

    *this = *ptr;
    // todo check if size in header (aka Tram::Serializable) is the good one
}