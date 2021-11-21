/*
** EPITECH PROJECT, 2021
** GetRoomList.cpp
** File description:
** TODO: add description
*/

#include "Network/Tram/GetRoomList.hpp"

using namespace Tram;

GetRoomList::GetRoomList() : Tram::Serializable(Tram::TramType::GET_ROOM_LIST, sizeof(GetRoomList))
{
    std::memset(list, 0, ROOM_LIST_SIZE);
}

GetRoomList::GetRoomList(const std::vector<size_t> &roomIdList)
    : Tram::Serializable(Tram::TramType::GET_ROOM_LIST, sizeof(GetRoomList))
{
    size_t listSize = roomIdList.size();

    std::memset(list, 0, ROOM_LIST_SIZE);
    for (size_t i = 0; i < listSize && i < ROOM_LIST_SIZE; i++) {
        this->list[i] = roomIdList[i];
    }
    this->nbItem = listSize <= 10 ? listSize : 10;
}

GetRoomList::~GetRoomList()
{
}

uint8_t *GetRoomList::serialize() const
{
    size_t len = this->length();
    auto *buffer = new uint8_t[len];

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