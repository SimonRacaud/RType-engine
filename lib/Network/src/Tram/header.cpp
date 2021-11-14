/*
** EPITECH PROJECT, 2021
** header.cpp
** File description:
** TODO: add description
*/

#include "Tram/header.hpp"

using namespace Tram;

header::header(TramType type, size_t size) : size(size), type(type)
{
}

uint8_t *header::serialize() const
{
    size_t length = this->length();
    auto *buffer = new uint8_t[length];

    std::memcpy(buffer, (void *) this, length);
    return buffer;
}

void header::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<header *>(buffer);

    if (this->magic != ptr->magic) {
        throw std::invalid_argument("header::deserialize invalid magic number");
    }
    this->size = ptr->size;
    this->type = ptr->type;
}

size_t header::length() const
{
    return sizeof(header);
}
header::header(uint8_t *data)
{
    auto *ptr = reinterpret_cast<header *>(data);

    if (this->magic != ptr->magic) {
        throw std::invalid_argument("header::deserialize invalid magic number");
    }
    this->size = ptr->size;
    this->type = ptr->type;
}