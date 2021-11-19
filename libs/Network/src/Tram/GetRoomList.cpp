/*
** EPITECH PROJECT, 2021
** GetRoomList.cpp
** File description:
** TODO: add description
*/

#include "Tram/GetRoomList.hpp"

using namespace Tram;

GetRoomList::GetRoomList() : Tram::Serializable(Tram::TramType::GET_ROOM_LIST, sizeof(GetRoomList))
{
}

GetRoomList::GetRoomList(const std::vector<size_t> &roomIdList)
    : Tram::Serializable(Tram::TramType::GET_ROOM_LIST, sizeof(GetRoomList))
{
    size_t listSize = roomIdList.size();

    for (size_t i = 0; i < listSize && i < 10; i++) {
        this->list[i] = roomIdList[i];
    }
    this->nbItem = listSize <= 10 ? listSize : 10;
}

GetRoomList::~GetRoomList()
{
}

uint8_t *GetRoomList::serialize() const
{
    size_t size = this->length();
    auto *buffer = new uint8_t[size];

    std::memset(buffer, 0, size);
    std::memcpy(buffer, (void *) this, sizeof(GetRoomList));

    return buffer;
}

void GetRoomList::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<GetRoomList *>(buffer);

    this->nbItem = ptr->nbItem;
    std::memcpy(this->list, ptr->list, sizeof(size_t) * this->nbItem);
}

size_t GetRoomList::length() const
{
    return sizeof(GetRoomList);
}

GetRoomList::GetRoomList(uint8_t *buffer) : Tram::Serializable(Tram::TramType::GET_ROOM_LIST, sizeof(GetRoomList))
{
    GetRoomList::deserialize(buffer);
}