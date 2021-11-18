/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include <unordered_map>

using namespace Network;

class intWrapperUDPserver {
  public:
    intWrapperUDPserver() = default;
    explicit intWrapperUDPserver(int val) : _val(val){};
    ~intWrapperUDPserver() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapperUDPserver);
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
        auto data(new uint8_t[sizeof(intWrapperUDPserver)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }

    intWrapperUDPserver(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapperUDPserver)) {
            return;
        }
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{222};
    int _otherVal{444};
};

/**
 * @brief Test
 *  AsioConnectionUDP::startAccept()
 *  AsioConnectionUDP::receiveAny()
 * @return 0 if test succeeded
 */
int testUDPserverAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<intWrapperUDPserver, std::size_t, std::string, std::size_t> recvData;
    AsioConnectionUDP<intWrapperUDPserver> server(portServer);
    intWrapperUDPserver my_var;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_var = std::get<0>(recvData);
            if (my_var.getVal() == 888 && my_var.getOtherVal() == 333)
                return 0;
            else {
                break;
            }
        }
    }
    return 84;
}