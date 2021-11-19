/*
** EPITECH PROJECT, 2021
** testClientTCPdataWrapper.cpp
** File description:
** test network TCP connection with data wrapper client side
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

template <Pointerable Data> static int startClientSendData(Data &dataToSend)
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    std::shared_ptr<IConnection<DataWrapper>> client(std::make_shared<AsioClientTCP<DataWrapper>>());
    NetworkManager clientManager(client);
    usleep(300000); // wait for the server to setup
    bool connected = clientManager.connect(ipServer, portServer);

    if (!connected) {
        return 84;
    }
    clientManager.sendAll(dataToSend);
    usleep(300000); // wait for the server to receive
    return 0;
}

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testTCPclientNetworkManagerJoinRoom()
{
    Tram::JoinRoom my_data(876);

    return startClientSendData(my_data);
}

int testTCPclientNetworkManagerGetRoomList()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<std::size_t> listOfRooms;
    listOfRooms.emplace_back(222);
    listOfRooms.emplace_back(444);
    Tram::GetRoomList my_data{listOfRooms};

    return startClientSendData(my_data);
}

int testTCPclientNetworkManagerCreateEntityReply()
{
    Tram::CreateEntityReply my_data(
        123, true, 456, 789, "127.0.0.1", 8080, 321, "type", netVector2f(0, 0), netVector2f(0, 0));
    return startClientSendData(my_data);
}

int testTCPclientNetworkManagerCreateEntityRequest()
{
    Tram::CreateEntityRequest my_data(123, 456, "789", 321, netVector2f(0, 0), netVector2f(0, 0));

    return startClientSendData(my_data);
}

int testTCPclientNetworkManagerJoinCreateRoomReply()
{
    Tram::JoinCreateRoomReply my_data(true, 123456789, 987);

    return startClientSendData(my_data);
}

int testTCPclientNetworkManagerComponentSync()
{
    //    Tram::DestroyEntity my_data{9876544321, 665544};
    //
    //    return startClientSendData(my_data);
    return 84;
}

int testTCPclientNetworkManagerDestroyEntity()
{
    Tram::DestroyEntity my_data(987654321, 665544);

    return startClientSendData(my_data);
}