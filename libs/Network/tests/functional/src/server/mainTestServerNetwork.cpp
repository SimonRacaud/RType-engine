/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include <functional>
#include <stdexcept>
#include <string>
#include "serverTest.hpp"
#include <unordered_map>

/**
 * @brief A sample test function to be copied for other tests
 * @return 0 if succeed
 */
int testFunction()
{
    if (0 == 84)
        return 84;
    return 0;
}

static const std::unordered_map<int, std::function<int(void)>> testFunctions{
    {0, testFunction},
    {1, testTCPserverAcceptReceive},
    {2, testTCPserverDataWrapperJoinRoom},
    {3, testTCPserverDataWrapperGetRoomList},
    {4, testTCPserverDataWrapperCreateEntityReply},
    {5, testTCPserverDataWrapperCreateEntityRequest},
    {6, testTCPserverDataWrapperJoinCreateRoomReply},
    {7, testTCPserverDataWrapperComponentSync},
    {8, testTCPserverDataWrapperDestroyEntity},
    {9, testTCPserverNetworkManagerJoinRoom},
    {10, testTCPserverNetworkManagerGetRoomList},
    {11, testTCPserverNetworkManagerCreateEntityReply},
    {12, testTCPserverNetworkManagerCreateEntityRequest},
    {13, testTCPserverNetworkManagerJoinCreateRoomReply},
    {14, testTCPserverNetworkManagerComponentSync},
    {15, testTCPserverNetworkManagerDestroyEntity},
};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}