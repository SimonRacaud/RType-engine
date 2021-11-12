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

using namespace Network::Tram;

ComponentSync::ComponentSync(uint32_t networkId, Time timestamp, const std::type_index &componentType,
    size_t componentSize, void *component)
    : networkId(networkId), timestamp(timestamp), componentType(componentType.hash_code()),
      componentSize(componentSize), component(component)
{}

ComponentSync::~ComponentSync()
{
    if (component != nullptr) {
        delete static_cast<uint8_t *>(component);
        component = nullptr;
    }
}

uint8_t *ComponentSync::deserialize()
{
    this->size = COMP_SYNC_HEAD_SIZE + this->componentSize;
    if (this->component == nullptr) {
        throw std::logic_error("ComponentSync::deserialize null component");
    }
    uint8_t *buffer = new uint8_t[this->size];
    ComponentSync *ptr = reinterpret_cast<ComponentSync *>(buffer);

    std::memcpy(buffer, this, COMP_SYNC_HEAD_SIZE); // copy header
    ptr->component = static_cast<void *>(buffer + COMP_SYNC_HEAD_SIZE); // update header ptr
    std::memcpy(ptr->component, this->component, this->componentSize); // copy body
    return buffer;
}

void ComponentSync::serialize(uint8_t *buffer)
{
    ComponentSync *ptr = reinterpret_cast<ComponentSync *>(buffer);

    *this = *ptr;
}

ComponentSync &ComponentSync::operator=(ComponentSync &other)
{
    // copy header
    this->size = other.size;
    this->networkId = other.networkId;
    this->timestamp = other.timestamp;
    this->componentType = other.componentType;
    this->componentSize = other.componentSize;
    if (other.component == nullptr) {
        this->component = nullptr;
    } else {
        this->component = new uint8_t[this->componentSize]; // alloc body
        std::memcpy(this->component, other.component, this->componentSize); // copy body
    }
    return *this;
}

