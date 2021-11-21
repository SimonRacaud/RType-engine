/*
** EPITECH PROJECT, 2021
** testSErverTCPresponse.cpp
** File description:
** TODO: add description
*/

#include "AsioServerTCP.hpp"
#include "INetwork.hpp"
#include "NetworkManager.hpp"

using namespace Network;

static const std::size_t portServer(8080);
static const std::string ipServer("127.0.0.1");

static NetworkManager startServer()
{
    std::shared_ptr<IConnection<DataWrapper>> server(std::make_shared<AsioConnectionTCP<DataWrapper>>(portServer));
    NetworkManager serverManager(server);
    while (!serverManager.connect(ipServer, portServer + 1))
        ;

    return serverManager;
}

static std::pair<uint8_t *, std::string> receiveData(NetworkManager &serverManager)
{
    std::tuple<uint8_t *, std::pair<std::string, std::size_t>> recvData;

    while (true) {
        recvData = serverManager.receive();
        if (std::get<0>(recvData)) {
            return std::make_pair(std::get<0>(recvData), (std::get<1>(recvData)).first);
        }
    }
    return {nullptr, ""};
}

int testTCPresponseCreateEntity()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    auto serverManager(startServer());
    std::pair<uint8_t *, std::string> my_data(receiveData(serverManager));
    Tram::CreateEntityRequest clientRequest(my_data.first);
    auto clientIp(ipServer /*my_data.second*/);

    //    sleep(5);
    std::cout << "finished" << std::endl;
    std::cout << "server (received from client):" << std::endl;
    std::cout << " clientRequest.roomId : " << clientRequest.roomId << std::endl;
    std::cout << " clientRequest.id : " << clientRequest.id << std::endl;
    std::cout << " clientRequest.entityType : " << clientRequest.entityType << std::endl;
    std::cout << " clientRequest.timestamp : " << clientRequest.timestamp << std::endl;
    std::cout << " clientRequest.position.x : " << clientRequest.position.x << std::endl;
    std::cout << " clientRequest.position.y : " << clientRequest.position.y << std::endl;
    std::cout << " clientRequest.velocity.x : " << clientRequest.velocity.x << std::endl;
    std::cout << " clientRequest.velocity.y : " << clientRequest.velocity.y << std::endl;
    if (clientRequest.roomId == 123 && clientRequest.id == 456
        && std::string(clientRequest.entityType) == std::string("type") && clientRequest.timestamp == 321
        && clientRequest.position.x == 123 && clientRequest.position.y == 456 && clientRequest.velocity.x == 78
        && clientRequest.velocity.y == 90) {
        return 0;
    }
    Tram::CreateEntityReply response(
        111, true, 222, 333, ipServer, portServer, 444, "otherType", netVector2f(111, 222), netVector2f(333, 444));
    try {
        serverManager.send(response, clientIp);
        std::cout << "sent" << std::endl;
    } catch (const invalidConnection &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    //    sleep(2);
    return 0;
}