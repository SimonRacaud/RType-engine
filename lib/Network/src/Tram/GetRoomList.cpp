/*
** EPITECH PROJECT, 2021
** GetRoomList.cpp
** File description:
** TODO: add description
*/

#include "Tram/GetRoomList.hpp"

using namespace Tram;

GetRoomList::GetRoomList(const std::vector<size_t> &roomIdList)
{
    this->list = new size_t[roomIdList.size()];
    for (size_t i = 0; i < roomIdList.size(); i++) {
        this->list[i] = roomIdList[i];
    }
    this->nbItem = roomIdList.size();
}

GetRoomList::~GetRoomList()
{
    delete[] this->list;
}

uint8_t *GetRoomList::serialize() const
{
    size_t size = this->length();
    auto *buffer = new uint8_t[size];
    auto *ptr = reinterpret_cast<GetRoomList *>(buffer);

    // nb item
    std::memcpy(buffer, (void *) this, sizeof(GetRoomList));
    // list
    ptr->list = reinterpret_cast<size_t *>(buffer + sizeof(GetRoomList));
    if (this->list != nullptr) {
        std::memcpy(ptr->list, this->list, sizeof(size_t) * this->nbItem);
    } else {
        ptr->list = nullptr;
    }
    return buffer;
}

void GetRoomList::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<GetRoomList *>(buffer);

    this->nbItem = ptr->nbItem;
    if (ptr->list == nullptr) {
        this->list = nullptr;
    } else {
        this->list = new size_t[this->nbItem];
        std::memcpy(this->list, ptr->list, sizeof(size_t) * nbItem);
    }
}

size_t GetRoomList::length() const
{
    return sizeof(GetRoomList) + (sizeof(size_t) * this->nbItem);
}
GetRoomList::GetRoomList(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<GetRoomList *>(buffer);

    this->nbItem = ptr->nbItem;
    if (ptr->list == nullptr) {
        this->list = nullptr;
    } else {
        this->list = new size_t[this->nbItem];
        std::memcpy(this->list, ptr->list, sizeof(size_t) * nbItem);
    }
}