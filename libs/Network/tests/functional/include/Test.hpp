/*
** EPITECH PROJECT, 2021
** intWrapper.hpp
** File description:
** fake data wrapper
*/

#ifndef R_TYPE_INTWRAPPER_HPP
#define R_TYPE_INTWRAPPER_HPP

#include "Network/Serializable.hpp"
#include "Network/Tram/ComponentSync.hpp"
#include "Network/Tram/CreateEntityReply.hpp"
#include "Network/Tram/CreateEntityRequest.hpp"
#include "Network/Tram/DestroyEntity.hpp"
#include "Network/Tram/EndGame.hpp"
#include "Network/Tram/GetRoomList.hpp"
#include "Network/Tram/JoinCreateRoomReply.hpp"
#include "Network/Tram/JoinRoom.hpp"
#include "Network/Tram/TramType.hpp"

class intWrapper {
  public:
    intWrapper() = default;
    explicit intWrapper(int val) : _val(val){};
    ~intWrapper() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapper);
    }

    [[nodiscard]] int getVal() const
    {
        return _val;
    }

    [[nodiscard]] int getOtherVal() const
    {
        return _otherVal;
    }

    [[nodiscard]] uint8_t *serialize() const
    {
        auto data(new uint8_t[sizeof(intWrapper)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }

    intWrapper(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapper)) {
            return;
        }
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{111};
    int _otherVal{333};
};

class TestComponent {
  public:
    explicit TestComponent(size_t number) : _number(number)
    {
    }

    size_t _number{424};
};

#endif // R_TYPE_INTWRAPPER_HPP