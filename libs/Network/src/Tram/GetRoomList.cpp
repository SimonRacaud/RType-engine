/*
** EPITECH PROJECT, 2021
** GetRoomList.cpp
** File description:
** TODO: add description
*/

#include "Tram/GetRoomList.hpp"

using namespace Tram;

GetRoomList::GetRoomList() : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(GetRoomList))
{
}

GetRoomList::GetRoomList(const std::vector<size_t> &roomIdList)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(GetRoomList))
{
    auto listSize(roomIdList.size());

    this->list = new size_t[listSize];
    for (size_t i = 0; i < listSize; i++) {
        this->list[i] = roomIdList[i];
    }
    this->nbItem = listSize;
    Serializable::size += (sizeof(size_t) * this->nbItem);
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
        std::memcpy(
            this->list, buffer + sizeof(GetRoomList),
            sizeof(size_t) * this->nbItem);
    }
    Serializable::size = sizeof(GetRoomList) + (sizeof(size_t) * this->nbItem);
}

size_t GetRoomList::length() const
{
    return Serializable::size;
}

GetRoomList::GetRoomList(uint8_t *buffer)
    : Tram::Serializable(Tram::TramType::CREATE_ENTITY_REPLY, sizeof(GetRoomList))
{
    GetRoomList::deserialize(buffer);
}