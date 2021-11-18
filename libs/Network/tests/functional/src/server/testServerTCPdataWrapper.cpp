/*
** EPITECH PROJECT, 2021
** testServerTCPdataWrapper.cpp
** File description:
** test network TCP connection with data wrapper server side
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "DataWrapper.hpp"
#include "Tram/JoinRoom.hpp"
#include <unordered_map>

using namespace Network;

static DataWrapper startServerGetData()
{
    const std::size_t portServer(8080);
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioServerTCP<DataWrapper> server(portServer);


    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            return std::get<0>(recvData);
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
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
int testTCPserverDataWrapperJoinRoom()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::JoinRoom my_data(my_wrapper.serialize());

    if (my_data.roomId == 51) {
        return 0;
    }
    return 84;
}

int testTCPserverDataWrapperGetRoomList()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::GetRoomList my_data{my_wrapper.serialize()};

    if (my_data.nbItem == 2 && my_data.list[0] == 222 && my_data.list[1] == 444) {
        return 0;
    }
    return 84;
}

int testTCPserverDataWrapperCreateEntityReply()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::CreateEntityReply my_data{my_wrapper.serialize()};

    if (my_data.roomId == 123 && my_data.accept == true && my_data.entityId == 456 && my_data.networkId == 789) {
        return 0;
    }
    return 84;
}

int testTCPserverDataWrapperCreateEntityRequest()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::CreateEntityRequest my_data{my_wrapper.serialize()};

    if (my_data.roomId == 123 && my_data.id == 456 && std::string(my_data.entityType) == std::string("789")
        && my_data.timestamp == 321) {
        return 0;
    }
    return 84;
}

int testTCPserverDataWrapperJoinCreateRoomReply()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::JoinCreateRoomReply my_data{my_wrapper.serialize()};

    if (my_data.accept == true && my_data.roomId == 123456789
        && my_data.startTimestamp == 987) {
        return 0;
    }
    return 84;
}

int testTCPserverDataWrapperComponentSync()
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

int testTCPserverDataWrapperDestroyEntity()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::DestroyEntity my_data{my_wrapper.serialize()};

    if (my_data.roomId == 987654321 && my_data.networkId == 665544) {
        return 0;
    }
    return 84;
}

// todo test all Trams