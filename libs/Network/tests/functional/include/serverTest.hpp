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

#endif // R_TYPE_SERVERTEST_HPP