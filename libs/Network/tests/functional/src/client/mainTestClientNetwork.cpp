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

static auto testNb(0);

static const std::unordered_map<int, std::function<int(void)>> testFunctions{
    {testNb, testFunction},
    {++testNb, testTCPclientConnectSendDisconnect},
    {++testNb, testTCPclientDataWrapperJoinRoom},
    {++testNb, testTCPclientDataWrapperGetRoomList},
    {++testNb, testTCPclientDataWrapperCreateEntityReply},
    {++testNb, testTCPclientDataWrapperCreateEntityRequest},
    {++testNb, testTCPclientDataWrapperJoinCreateRoomReply},
    {++testNb, testTCPclientDataWrapperComponentSync},
    {++testNb, testTCPclientDataWrapperDestroyEntity},
    {++testNb, testTCPclientNetworkManagerJoinRoom},
    {++testNb, testTCPclientNetworkManagerGetRoomList},
    {++testNb, testTCPclientNetworkManagerCreateEntityReply},
    {++testNb, testTCPclientNetworkManagerCreateEntityRequest},
    {++testNb, testTCPclientNetworkManagerJoinCreateRoomReply},
    {++testNb, testTCPclientNetworkManagerComponentSync},
    {++testNb, testTCPclientNetworkManagerDestroyEntity},
    {++testNb, testUDPclientConnectSendDisconnect},
    {++testNb, testUDPclientDataWrapperJoinRoom},
    {++testNb, testUDPclientDataWrapperGetRoomList},
    {++testNb, testUDPclientDataWrapperCreateEntityReply},
    {++testNb, testUDPclientDataWrapperCreateEntityRequest},
    {++testNb, testUDPclientDataWrapperJoinCreateRoomReply},
    {++testNb, testUDPclientDataWrapperComponentSync},
    {++testNb, testUDPclientDataWrapperDestroyEntity},
    {++testNb, testUDPclientNetworkManagerJoinRoom},
    {++testNb, testUDPclientNetworkManagerGetRoomList},
    {++testNb, testUDPclientNetworkManagerCreateEntityReply},
    {++testNb, testUDPclientNetworkManagerCreateEntityRequest},
    {++testNb, testUDPclientNetworkManagerJoinCreateRoomReply},
    {++testNb, testUDPclientNetworkManagerComponentSync},
    {++testNb, testUDPclientNetworkManagerDestroyEntity},
    {++testNb, testUDPclientDisconnection},

};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}