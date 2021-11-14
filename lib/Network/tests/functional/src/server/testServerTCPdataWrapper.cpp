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
 *  // todo add datawrapper
 * @return 0 if test succeeded
 */
int testServerAcceptReceiveDataWrapper()
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
            std::cerr << "my_data.roomId " << my_data.roomId << std::endl;
            if (my_data.roomId == 51)
                return 0;
            else
                break;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    std::cout << " returned 84" << std::endl;
    return 84;
}