/*
** EPITECH PROJECT, 2021
** serverTest.hpp
** File description:
** prototypes of test functions, server side
*/
#ifndef R_TYPE_SERVERTEST_HPP
#define R_TYPE_SERVERTEST_HPP

int testTCPserverAcceptReceive();

int testTCPserverDataWrapperJoinRoom();
int testTCPserverDataWrapperGetRoomList();
int testTCPserverDataWrapperCreateEntityReply();
int testTCPserverDataWrapperCreateEntityRequest();
int testTCPserverDataWrapperJoinCreateRoomReply();
int testTCPserverDataWrapperComponentSync();
int testTCPserverDataWrapperDestroyEntity();

int testTCPserverNetworkManagerJoinRoom();
int testTCPserverNetworkManagerGetRoomList();
int testTCPserverNetworkManagerCreateEntityReply();
int testTCPserverNetworkManagerCreateEntityRequest();
int testTCPserverNetworkManagerJoinCreateRoomReply();
int testTCPserverNetworkManagerComponentSync();
int testTCPserverNetworkManagerDestroyEntity();

int testUDPserverAcceptReceive();

int testUDPserverDataWrapperJoinRoom();
int testUDPserverDataWrapperGetRoomList();
int testUDPserverDataWrapperCreateEntityReply();
int testUDPserverDataWrapperCreateEntityRequest();
int testUDPserverDataWrapperJoinCreateRoomReply();
int testUDPserverDataWrapperComponentSync();
int testUDPserverDataWrapperDestroyEntity();

int testUDPserverNetworkManagerJoinRoom();
int testUDPserverNetworkManagerGetRoomList();
int testUDPserverNetworkManagerCreateEntityReply();
int testUDPserverNetworkManagerCreateEntityRequest();
int testUDPserverNetworkManagerJoinCreateRoomReply();
int testUDPserverNetworkManagerComponentSync();
int testUDPserverNetworkManagerDestroyEntity();

#endif // R_TYPE_SERVERTEST_HPP