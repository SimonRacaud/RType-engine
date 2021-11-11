/*
** EPITECH PROJECT, 2021
** testServerTCPdataWrapper.cpp
** File description:
** test network TCP connection with data wrapper server side
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "DataWrapper.hpp"
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
    DataWrapper my_var;
    my_structData my_data{23};

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_var = std::get<0>(recvData);
            //            std::cout << "my_var.getVal() : " << my_var.getVal() << std::endl;
            //            std::cout << "my_var.getOhterVal() : " << my_var.getOtherVal() << std::endl;
            my_data = my_var.getData<my_structData>();
            std::cout << my_data.testValue << std::endl;
            std::cout << std::endl;
            return 0;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    return 84;
}