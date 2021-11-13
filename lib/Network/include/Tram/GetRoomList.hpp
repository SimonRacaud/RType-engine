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

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include "ISerializable.hpp"

namespace Tram
{
    class GetRoomList : public Network::ISerializable {
      public:
        GetRoomList() = default;
        explicit GetRoomList(std::vector<size_t> const &roomIdList);
        ~GetRoomList() override;

        size_t nbItem{0};
        size_t *list{nullptr};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit GetRoomList(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // GETROOMLIST_HPP