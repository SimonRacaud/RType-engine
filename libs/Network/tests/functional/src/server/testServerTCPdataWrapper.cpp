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

/**
 * @brief Test
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testServerDataWrapperJoinRoom()
{
    const std::size_t portServer(8080);
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioServerTCP<DataWrapper> server(portServer);
    DataWrapper my_wrapper;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_wrapper = std::get<0>(recvData);
            Tram::JoinRoom my_data(my_wrapper.serialize());
            if (my_data.roomId == 51)
                return 0;
            else
                break;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    return 84;
}

int testServerDataWrapperGetRoomList()
{
    const std::size_t portServer(8080);
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioServerTCP<DataWrapper> server(portServer);
    DataWrapper my_wrapper;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_wrapper = std::get<0>(recvData);
            Tram::GetRoomList my_data{my_wrapper.serialize()};
            if (my_data.nbItem == 2 && my_data.list[0] == 222 && my_data.list[1] == 444) {
                return 0;
            } else
                break;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    return 84;
}

// todo test all Trams