/*
** EPITECH PROJECT, 2021
** DataWrapper.cpp
** File description:
 * ** Wraps data to be sent on network

*/

#include "DataWrapper.hpp"

std::size_t DataWrapper::length() const
{
    return _dataLength;
}

DataWrapper::DataWrapper(const uint8_t *data, const std::size_t length)
{
    DataWrapper::deserialize(data, length);
}

void DataWrapper::deserialize(const uint8_t *data, const std::size_t length)
{
    delete _data;
    _data = nullptr;
    _dataLength = 0;
    if (data && length) {
        _data = new uint8_t[length];
        memcpy(_data, data, length);
        _dataLength = length;
    }
}

uint8_t *DataWrapper::serialize() const
{
    if (!_dataLength) {
        return nullptr;
    }
    auto tmp = new uint8_t[_dataLength];

    memcpy(tmp, _data, _dataLength);
    return tmp;
}