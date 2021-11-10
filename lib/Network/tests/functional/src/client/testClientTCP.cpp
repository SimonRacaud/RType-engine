/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include <unordered_map>

using namespace Network;

class intWrapper {
  public:
    intWrapper() = default;
    intWrapper(int val) : _val(val){};
    ~intWrapper() = default;

    std::size_t size() const
    {
        return sizeof(int);
    }

    int getVal()
    {
        return _val;
    }

  private:
    int _val{111};
};

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 * @return 0 if test succeeded
 */
int testClientConnectSendDisconnect()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    intWrapper myData(888);
    AsioClientTCP<intWrapper> client; // TODO DATA replace by type
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}