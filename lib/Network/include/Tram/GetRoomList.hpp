/*
** EPITECH PROJECT , 2021
** GetRoomList
** File description:
** \file GetRoomList.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef GETROOMLIST_HPP
#define GETROOMLIST_HPP

#include <cstring>
#include <inttypes.h>
#include <stddef.h>
#include <string>
#include <vector>
#include "ISerializable.hpp"

namespace Tram
{
    class GetRoomList : public Network::ISerializable {
      public:
        GetRoomList() = default;
        GetRoomList(std::vector<size_t> const &roomIdList);
        virtual ~GetRoomList();

        size_t nbItem{0};
        size_t *list{nullptr};

        virtual uint8_t *serialize();
        virtual void deserialize(uint8_t *buffer);
        virtual size_t length() const;
    };

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
        if (this->list != nullptr) {
            delete[] this->list;
        }
    }

    uint8_t *GetRoomList::serialize()
    {
        size_t size = this->length();
        uint8_t *buffer = new uint8_t[size];
        GetRoomList *ptr = reinterpret_cast<GetRoomList *>(buffer);

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
        GetRoomList *ptr = reinterpret_cast<GetRoomList *>(buffer);

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
} // namespace Tram

#endif // GETROOMLIST_HPP