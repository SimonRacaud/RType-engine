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
    delete _data;
    if (data) {
        _data = new uint8_t[length];
        memcpy(_data, data, length);
        _dataLength = length;
    } else {
        _data = nullptr;
    }
}

void DataWrapper::deserialize(const uint8_t *data, const std::size_t length)
{
    delete _data;
    if (data) {
        _data = new uint8_t[length];
        memcpy(_data, data, length);
        _dataLength = length;
    } else {
        _data = nullptr;
    }
}
uint8_t *DataWrapper::serialize() const
{
    return _data;
}