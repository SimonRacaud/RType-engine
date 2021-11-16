/*
** EPITECH PROJECT, 2021
** testClientUDPdataWrapper.cpp
** File description:
** test network UDP connection with data wrapper client side
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

template <Pointerable Data> static int startClientSendData(Data &dataToSend)
{
    const std::size_t portClient(8081);
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    std::shared_ptr<IConnection<DataWrapper>> client(std::make_shared<AsioConnectionUDP<DataWrapper>>(portClient));
    NetworkManager clientManager(client);
    usleep(300000); // wait for the server to setup
    bool connected = clientManager.connect(ipServer, portServer);

    if (!connected) {
        return 84;
    }
    clientManager.sendAll(dataToSend);
    return 0;
}

/**
 * @brief Test
 *  AsioConnectionUDP::connect()
 *  AsioConnectionUDP::send()
 *  AsioConnectionUDP::disconnect()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testUDPclientNetworkManagerJoinRoom()
{
    Tram::JoinRoom my_data{876};

    return startClientSendData(my_data);
}

int testUDPclientNetworkManagerGetRoomList()
{
    std::vector<std::size_t> listOfRooms{222, 444};
    Tram::GetRoomList my_data{listOfRooms};

    return startClientSendData(my_data);
}

int testUDPclientNetworkManagerCreateEntityReply()
{
    Tram::CreateEntityReply my_data{123, true, 456, 789};
    return startClientSendData(my_data);
}

int testUDPclientNetworkManagerCreateEntityRequest()
{
    Tram::CreateEntityRequest my_data{123, 456, "789", std::chrono::milliseconds(321)};

    return startClientSendData(my_data);
}

int testUDPclientNetworkManagerJoinCreateRoomReply()
{
    Tram::JoinCreateRoomReply my_data{true, 123456789, std::chrono::milliseconds(987)};

    return startClientSendData(my_data);
}

int testUDPclientNetworkManagerComponentSync()
{
    //    Tram::DestroyEntity my_data{9876544321, 665544};
    //
    //    return startClientSendData(my_data);
    return 84;
}

int testUDPclientNetworkManagerDestroyEntity()
{
    Tram::DestroyEntity my_data{987654321, 665544};

    return startClientSendData(my_data);
}