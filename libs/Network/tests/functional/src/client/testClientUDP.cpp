/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"

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
        return _val + _otherVal;
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
        if (len != sizeof(intWrapper))
            return;
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{111};
    int _otherVal{333};
};

/**
 * @brief Test
 *  AsioConnectionUDP::connect()
 *  AsioConnectionUDP::send()
 *  AsioConnectionUDP::disconnect()
 * @return 0 if test succeeded
 */
int testUDPclientConnectSendDisconnect()
{
    const std::size_t portClient(8081);
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    intWrapper myData(888);
    AsioConnectionUDP<intWrapper> client(portClient);
    sleep(1); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}