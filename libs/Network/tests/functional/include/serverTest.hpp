/*
** EPITECH PROJECT, 2021
** serverTest.hpp
** File description:
** prototypes of test functions, server side
*/
#ifndef R_TYPE_SERVERTEST_HPP
#define R_TYPE_SERVERTEST_HPP

int testServerAcceptReceive();

int testServerDataWrapperJoinRoom();
int testServerDataWrapperGetRoomList();
int testServerDataWrapperCreateEntityReply();
int testServerDataWrapperCreateEntityRequest();
int testServerDataWrapperJoinCreateRoomReply();
int testServerDataWrapperComponentSync();
int testServerDataWrapperDestroyEntity();

int testServerNetworkManagerJoinRoom();
int testServerNetworkManagerGetRoomList();
int testServerNetworkManagerCreateEntityReply();
int testServerNetworkManagerCreateEntityRequest();
int testServerNetworkManagerJoinCreateRoomReply();
int testServerNetworkManagerComponentSync();
int testServerNetworkManagerDestroyEntity();

#endif // R_TYPE_SERVERTEST_HPP