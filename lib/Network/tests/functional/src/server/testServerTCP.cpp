/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "DataWrapper.hpp"
#include <unordered_map>

using namespace Network;

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
            std::cout << "size not good" << std::endl;
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
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 * @return 0 if test succeeded
 */
int testServerAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<intWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioServerTCP<intWrapper> server(portServer);
    intWrapper my_var;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_var = std::get<0>(recvData);
            std::cout << "my_var.getVal() : " << my_var.getVal() << std::endl;
            std::cout << "my_var.getOhterVal() : " << my_var.getOtherVal() << std::endl;
            std::cout << std::endl;
            return 0;
        }
        //  todo set clock to avoid infinite loop
        //     in shell script ?
        //     with Clock class ?
    }
    return 84;
}