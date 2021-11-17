/*
** EPITECH PROJECT, 2021
** clientTest.hpp
** File description:
** prototypes of test functions, client side
*/

#ifndef R_TYPE_CLIENTTEST_HPP
#define R_TYPE_CLIENTTEST_HPP

int testTCPclientConnectSendDisconnect();

int testTCPclientDataWrapperJoinRoom();
int testTCPclientDataWrapperGetRoomList();
int testTCPclientDataWrapperCreateEntityReply();
int testTCPclientDataWrapperCreateEntityRequest();
int testTCPclientDataWrapperJoinCreateRoomReply();
int testTCPclientDataWrapperComponentSync();
int testTCPclientDataWrapperDestroyEntity();

int testTCPclientNetworkManagerJoinRoom();
int testTCPclientNetworkManagerGetRoomList();
int testTCPclientNetworkManagerCreateEntityReply();
int testTCPclientNetworkManagerCreateEntityRequest();
int testTCPclientNetworkManagerJoinCreateRoomReply();
int testTCPclientNetworkManagerComponentSync();
int testTCPclientNetworkManagerDestroyEntity();

int testUDPclientConnectSendDisconnect();

int testUDPclientDataWrapperJoinRoom();
int testUDPclientDataWrapperGetRoomList();
int testUDPclientDataWrapperCreateEntityReply();
int testUDPclientDataWrapperCreateEntityRequest();
int testUDPclientDataWrapperJoinCreateRoomReply();
int testUDPclientDataWrapperComponentSync();
int testUDPclientDataWrapperDestroyEntity();

int testUDPclientNetworkManagerJoinRoom();
int testUDPclientNetworkManagerGetRoomList();
int testUDPclientNetworkManagerCreateEntityReply();
int testUDPclientNetworkManagerCreateEntityRequest();
int testUDPclientNetworkManagerJoinCreateRoomReply();
int testUDPclientNetworkManagerComponentSync();
int testUDPclientNetworkManagerDestroyEntity();

int testUDPclientDisconnection();

#endif // R_TYPE_CLIENTTEST_HPP