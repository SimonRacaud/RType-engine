/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include "intWrapper.hpp"
#include "serverTest.hpp"
#include <unordered_map>

using namespace Network;

/**
 * @brief Test
 *  AsioConnectionUDP::startAccept()
 *  AsioConnectionUDP::receiveAny()
 * @return 0 if test succeeded
 */
int testUDPserverAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<intWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioConnectionUDP<intWrapper> server(portServer);

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            intWrapper my_var((uint8_t *) std::get<0>(recvData).serialize(), std::get<1>(recvData));
            if (my_var.getVal() == 888 && my_var.getOtherVal() == 333) {
                return 0;
            } else {
                break;
            }
        }
    }
    return 84;
}