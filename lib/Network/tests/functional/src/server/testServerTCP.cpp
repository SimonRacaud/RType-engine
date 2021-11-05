/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include <unordered_map>

static const std::size_t PACKETSIZE = 123;

using namespace Network;
/**
 * @brief Test
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 * @return 0 if test succeeded
 */
int testServerAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> recvData;
    AsioServerTCP<PACKETSIZE> server(portServer);

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            std::cout.write(std::get<0>(recvData).data(), std::get<1>(recvData));
            std::cout << std::endl;
            return 0;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    return 84;
}