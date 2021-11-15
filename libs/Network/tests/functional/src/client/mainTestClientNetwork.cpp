/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <functional>
#include <stdexcept>
#include <string>
#include "clientTest.hpp"
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

static const std::unordered_map<int, std::function<int(void)>> testFunctions{{0, testFunction},
    {1, testClientConnectSendDisconnect}, {2, testClientDataWrapperJoinRoom}, {3, testClientDataWrapperGetRoomList},
    {4, testClientDataWrapperCreateEntityReply}, {5, testClientDataWrapperCreateEntityRequest},
    {6, testClientDataWrapperJoinCreateRoomReply}, {7, testClientDataWrapperComponentSync},
    {8, testClientDataWrapperDestroyEntity}, {9, testClientNetworkManagerJoinRoom},
    {10, testClientNetworkManagerGetRoomList}, {11, testClientNetworkManagerCreateEntityReply},
    {12, testClientNetworkManagerCreateEntityRequest}, {13, testClientNetworkManagerJoinCreateRoomReply},
    {14, testClientNetworkManagerComponentSync}, {15, testClientNetworkManagerDestroyEntity}};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}