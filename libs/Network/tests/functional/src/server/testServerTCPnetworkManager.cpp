/*
** EPITECH PROJECT, 2021
** testServerTCPnetworkManager.cpp
** File description:
** test network TCP connection with data wrapper server side
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"
#include <unordered_map>

using namespace Network;

static uint8_t *startServerGetData()
{
    const std::size_t portServer(8080);
    std::tuple<uint8_t *, std::pair<std::string, std::size_t>> recvData;
    std::shared_ptr<IConnection<DataWrapper>> server(std::make_shared<AsioServerTCP<DataWrapper>>(portServer));
    NetworkManager serverManager(server);

    while (true) {
        recvData = serverManager.receive();
        if (std::get<0>(recvData)) {
            return std::get<0>(recvData);
        }
    }
    exit(84);
}
/**
 * @brief Test
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testTCPserverNetworkManagerJoinRoom()
{
    Tram::JoinRoom my_data(startServerGetData());

    if (my_data.roomId == 876) {
        return 0;
    }
    return 84;
}

int testTCPserverNetworkManagerGetRoomList()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Tram::GetRoomList my_data{startServerGetData()};

    if (my_data.nbItem == 2 && my_data.list[0] == 222 && my_data.list[1] == 444) {
        return 0;
    }
    return 84;
}

int testTCPserverNetworkManagerCreateEntityReply()
{
    Tram::CreateEntityReply my_data{startServerGetData()};

    if (my_data.roomId == 123 && my_data.accept == true && my_data.entityId == 456 && my_data.networkId == 789) {
        return 0;
    }
    return 84;
}

int testTCPserverNetworkManagerCreateEntityRequest()
{
    Tram::CreateEntityRequest my_data(startServerGetData());

    if (my_data.roomId == 123 && my_data.id == 456 && std::string(my_data.entityType) == std::string("789")
        && my_data.timestamp == 321) {
        return 0;
    }
    return 84;
}

int testTCPserverNetworkManagerJoinCreateRoomReply()
{
    Tram::JoinCreateRoomReply my_data(startServerGetData());

    if (my_data.accept == true && my_data.roomId == 123456789 && my_data.startTimestamp == 987) {
        return 0;
    }
    return 84;
}

int testTCPserverNetworkManagerComponentSync()
{
    // size_t roomId{0}
    // size_t size{0}
    // uint32_t networkId{0}
    // Time timestamp{0}
    // size_t componentType{0}
    // size_t componentSize{0}
    // void *component{nullptr}
    //    DataWrapper my_wrapper(startServerGetData());
    //    Tram::ComponentSync my_data{my_wrapper.serialize()};

    //    if (!my_wrapper.serialize())
    //        return 0;
    //    if (my_data.roomId == 123 && my_data.accept == true && my_data.entityId == 456 && my_data.networkId == 789) {
    //        return 0;
    //    }
    return 84;
}

int testTCPserverNetworkManagerDestroyEntity()
{
    Tram::DestroyEntity my_data(startServerGetData());

    if (my_data.roomId == 987654321 && my_data.networkId == 665544) {
        return 0;
    }
    return 84;
}