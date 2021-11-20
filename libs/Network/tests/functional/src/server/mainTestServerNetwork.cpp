/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

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

static auto testNb(0);

static const std::unordered_map<int, std::function<int(void)>> testFunctions{
    {testNb, testFunction},
    {++testNb, testTCPserverAcceptReceive},
    {++testNb, testTCPserverDataWrapperJoinRoom},
    {++testNb, testTCPserverDataWrapperGetRoomList},
    {++testNb, testTCPserverDataWrapperCreateEntityReply},
    {++testNb, testTCPserverDataWrapperCreateEntityRequest},
    {++testNb, testTCPserverDataWrapperJoinCreateRoomReply},
    {++testNb, testTCPserverDataWrapperComponentSync},
    {++testNb, testTCPserverDataWrapperDestroyEntity},
    {++testNb, testTCPserverNetworkManagerJoinRoom},
    {++testNb, testTCPserverNetworkManagerGetRoomList},
    {++testNb, testTCPserverNetworkManagerCreateEntityReply},
    {++testNb, testTCPserverNetworkManagerCreateEntityRequest},
    {++testNb, testTCPserverNetworkManagerJoinCreateRoomReply},
    {++testNb, testTCPserverNetworkManagerComponentSync},
    {++testNb, testTCPserverNetworkManagerDestroyEntity},
    {++testNb, testUDPserverAcceptReceive},
    {++testNb, testUDPserverDataWrapperJoinRoom},
    {++testNb, testUDPserverDataWrapperGetRoomList},
    {++testNb, testUDPserverDataWrapperCreateEntityReply},
    {++testNb, testUDPserverDataWrapperCreateEntityRequest},
    {++testNb, testUDPserverDataWrapperJoinCreateRoomReply},
    {++testNb, testUDPserverDataWrapperComponentSync},
    {++testNb, testUDPserverDataWrapperDestroyEntity},
    {++testNb, testUDPserverNetworkManagerJoinRoom},
    {++testNb, testUDPserverNetworkManagerGetRoomList},
    {++testNb, testUDPserverNetworkManagerCreateEntityReply},
    {++testNb, testUDPserverNetworkManagerCreateEntityRequest},
    {++testNb, testUDPserverNetworkManagerJoinCreateRoomReply},
    {++testNb, testUDPserverNetworkManagerComponentSync},
    {++testNb, testUDPserverNetworkManagerDestroyEntity},
    {++testNb, testUDPserverDisconnection},
    {++testNb, testTCPserverDisconnection},
    {++testNb, testTCPresponseCreateEntity},
};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}