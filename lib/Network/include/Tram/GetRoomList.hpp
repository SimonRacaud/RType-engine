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

#include <inttypes.h>
#include <stddef.h>
#include <string>
#include <cstring>
#include <vector>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        class GetRoomList : public ISerializable<GetRoomList> {
          public:
            GetRoomList(std::vector<size_t> const &roomIdList);
            virtual ~GetRoomList();

            size_t nbItem{0};
            size_t *list{nullptr};

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
            virtual size_t length() const;
        };

        GetRoomList::GetRoomList(const std::vector<size_t> &roomIdList)
        {
            this->list = new size_t[roomIdList.size()];
            for (size_t i = 0; i < roomIdList.size(); i++) {
                this->list[i] = roomIdList[i];
            }
        }

        GetRoomList::~GetRoomList()
        {
            if (list) {
                delete[] list;
            }
        }

        uint8_t *GetRoomList::deserialize()
        {
            size_t size = this->length();
            uint8_t *buffer = new uint8_t[size];
            GetRoomList *ptr = reinterpret_cast<GetRoomList *>(buffer);

            // nb item
            std::memcpy(buffer, (void*)this, sizeof(size_t));
            // list
            ptr->list = reinterpret_cast<size_t *>(buffer + (sizeof(size_t) + sizeof(size_t *)));
            std::memcpy(ptr->list, this->list, sizeof(size_t) * this->nbItem);
            return buffer;
        }

        void GetRoomList::serialize(uint8_t *buffer)
        {
            GetRoomList *ptr = reinterpret_cast<GetRoomList *>(buffer);

            this->nbItem = ptr->nbItem;
            if (this->list == nullptr) {
                this->list = nullptr;
            } else {
                this->list = new size_t[this->nbItem];
                std::memcpy(this->list, ptr->list, sizeof(size_t) * nbItem);
            }
        }

        size_t GetRoomList::length() const
        {
            return sizeof(size_t) * (this->nbItem + 1) + sizeof(size_t *);
        }
    }
}

#endif // GETROOMLIST_HPP
