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
    {1, testServerAcceptReceive},
    {2, testServerDataWrapperJoinRoom},
    {3, testServerDataWrapperGetRoomList},
    {4, testServerDataWrapperCreateEntityReply},
    {5, testServerDataWrapperCreateEntityRequest},
    {6, testServerDataWrapperJoinCreateRoomReply},
    {7, testServerDataWrapperComponentSync},
    {8, testServerDataWrapperDestroyEntity},
    {9, testServerNetworkManagerJoinRoom},
    {10, testServerNetworkManagerGetRoomList},
    {11, testServerNetworkManagerCreateEntityReply},
    {12, testServerNetworkManagerCreateEntityRequest},
    {13, testServerNetworkManagerJoinCreateRoomReply},
    {14, testServerNetworkManagerComponentSync},
    {15, testServerNetworkManagerDestroyEntity},
};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}