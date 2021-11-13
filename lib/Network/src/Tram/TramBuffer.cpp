/*
** EPITECH PROJECT, 2021
** TramBuffer.cpp
** File description:
** Implementation of TramBufferClass
*/

#include "Tram/TramBuffer.hpp"
#include <exception>

void Tram::TramBuffer::SetData(uint8_t *data, size_t length)
{
    if (!_dataLength)
        throw std::invalid_argument("Size of data is 0");
    auto *tmp(new uint8_t[_dataLength + length]);

    std::memcpy(tmp, _data, _dataLength);
    std::memcpy(tmp + _dataLength, data, length);
    _dataLength += length;
    delete _data;
    _data = tmp;
}

std::size_t Tram::TramBuffer::getTramSize()
{
    return Tram::header(_data).size;
}

bool Tram::TramBuffer::isTramComplete()
{
    if (sizeof(Tram::header) + getTramSize() <= _dataLength)
        return true;
    return false;
}

uint8_t *Tram::TramBuffer::receiveTram()
{
    if (!isTramComplete())
        return nullptr;
    auto tramSize(getTramSize());
    auto tmp(new uint8_t[tramSize]);

    memmove(tmp, _data + sizeof(Tram::header), tramSize);
    _dataLength -= sizeof(Tram::header) + tramSize;
    memmove(_data, _data + (sizeof(Tram::header) + tramSize), _dataLength);
    return tmp;
}