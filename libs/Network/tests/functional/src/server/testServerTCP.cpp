/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "intWrapper.hpp"
#include "serverTest.hpp"
#include <unordered_map>

using namespace Network;

/**
 * @brief Test
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 * @return 0 if test succeeded
 */
int testTCPserverAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<intWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioConnectionTCP<intWrapper> server(portServer);
    intWrapper my_var;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            my_var = std::get<0>(recvData);
            if (my_var.getVal() == 888 && my_var.getOtherVal() == 333)
                return 0;
            else {
                break;
            }
        }
    }
    return 84;
}