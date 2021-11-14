/*
** EPITECH PROJECT, 2021
** header.cpp
** File description:
** TODO: add description
*/

#include "Tram/Serializable.hpp"

using namespace Tram;

Serializable::Serializable(TramType type, size_t size) : size(size), type(type)
{
}

uint8_t *Serializable::serialize() const
{
    size_t length = this->length();
    auto *buffer = new uint8_t[length];

    std::memcpy(buffer, (void *) this, length);
    return buffer;
}

void Serializable::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<Serializable *>(buffer);

    if (this->magic != ptr->magic) {
        throw std::invalid_argument("Serializable::deserialize invalid magic number");
    }
    this->size = ptr->size;
    this->type = ptr->type;
}

size_t Serializable::length() const
{
    return sizeof(Serializable);
}
Serializable::Serializable(uint8_t *data)
{
    auto *ptr = reinterpret_cast<Serializable *>(data); // todo data is truncated

    if (this->magic != ptr->magic) {
        throw std::invalid_argument("header::deserialize invalid magic number");
    }
    this->size = ptr->size;
    this->type = ptr->type;
}