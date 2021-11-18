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

class intWrapperUDPclient {
  public:
    intWrapperUDPclient() = default;
    explicit intWrapperUDPclient(int val) : _val(val){};
    ~intWrapperUDPclient() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapperUDPclient);
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
        auto data(new uint8_t[sizeof(intWrapperUDPclient)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }

    intWrapperUDPclient(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapperUDPclient)) {
            return;
        }
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
    intWrapperUDPclient myData(888);

    AsioConnectionUDP<intWrapperUDPclient> client(portClient);
    usleep(300000); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    usleep(300000); // wait for the server to receive
    client.disconnect(ipServer, portServer);
    return 0;
}