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

ComponentSync::ComponentSync(
    uint32_t networkId, Time timestamp, const std::type_index &componentType, size_t componentSize, void *component)
    : Tram::Serializable(Tram::TramType::SYNC_COMPONENT, sizeof(ComponentSync) + componentSize), networkId(networkId),
      timestamp(timestamp), componentType(componentType.hash_code()), componentSize(componentSize), component(component)
{
}

ComponentSync::~ComponentSync()
{
    if (component != nullptr) {
        delete static_cast<uint8_t *>(component);
        component = nullptr;
    }
}

uint8_t *ComponentSync::serialize() const
{
    //    this->size = this->length() + this->componentSize; // todo ask simon why this
    if (this->component == nullptr) {
        throw std::logic_error("ComponentSync::serialize null component");
    }
    auto *buffer = new uint8_t[this->length() + this->componentSize];
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