/*
** EPITECH PROJECT, 2021
** testClientTCPresponse.cpp
** File description:
** TODO: add description
*/

#include "AsioClientTCP.hpp"
#include "INetwork.hpp"
#include "NetworkManager.hpp"

using namespace Network;

static const std::string ipServer("127.0.0.1");
static const std::size_t portServer(8080);

static NetworkManager startClient()
{
    std::shared_ptr<IConnection<DataWrapper>> client(std::make_shared<AsioConnectionTCP<DataWrapper>>(portServer + 1));
    NetworkManager clientManager(client);
    //    usleep(300000); // wait for the server to setup

    return clientManager;
}

int testTCPresponseCreateEntity()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    Tram::CreateEntityRequest my_data(123, 456, "type", 789, netVector2f(123, 456), netVector2f(78, 90));
    NetworkManager clientManager(startClient());
    bool connected(false);

    while (!connected) {
        connected = clientManager.connect(ipServer, portServer);
    }

    if (!connected) {
        return 84;
    }
    clientManager.sendAll(my_data);
    //    usleep(300000); // wait for the server to receive
    std::tuple<uint8_t *, std::pair<std::string, std::size_t>> serverData(nullptr, {"", 0});
    while (!std::get<0>(serverData)) {
        serverData = clientManager.receive();
        //        std::cout << "hello in client loop" << std::endl;
    }

    Tram::CreateEntityReply serverTram(std::get<0>(serverData));
    auto serverIp(std::get<1>(serverData).first);

    std::cout << "client (received from server): " << std::endl;
    std::cout << "serverTram.roomId : " << serverTram.roomId << std::endl;
    std::cout << "serverTram.accept : " << serverTram.accept << std::endl;
    std::cout << "serverTram.entityId : " << serverTram.entityId << std::endl;
    std::cout << "serverTram.net./workId : " << serverTram.networkId << std::endl;
    std::cout << "serverTram.timestamp : " << serverTram.timestamp << std::endl;
    std::cout << "serverTram.position.x : " << serverTram.position.x << std::endl;
    std::cout << "serverTram.position.y : " << serverTram.position.y << std::endl;
    std::cout << "serverTram.velocity.x : " << serverTram.velocity.x << std::endl;
    std::cout << "serverTram.velocity.y : " << serverTram.velocity.y << std::endl;
    std::cout << "serverTram.port : " << serverTram.port << std::endl;
    std::cout << "serverTram.ip : " << serverTram.ip << std::endl;
    std::cout << "serverTram.entityType : " << serverTram.entityType << std::endl;

    if (serverTram.roomId == 111 && serverTram.accept && serverTram.entityId == 222 && serverTram.networkId == 333
        && serverTram.timestamp == 444 && serverTram.position.x == 111 && serverTram.position.y == 222
        && serverTram.velocity.x == 333 && serverTram.velocity.y == 444 && serverTram.port == 8080
        && serverTram.ip == ipServer && std::string(serverTram.entityType) == std::string("otherType")) {
        return 0;
    }

    return 84;
}