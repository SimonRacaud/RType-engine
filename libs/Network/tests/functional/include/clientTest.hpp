/*
** EPITECH PROJECT, 2021
** clientTest.hpp
** File description:
** prototypes of test functions, client side
*/

#ifndef R_TYPE_CLIENTTEST_HPP
#define R_TYPE_CLIENTTEST_HPP

int testClientConnectSendDisconnect();

int testClientDataWrapperJoinRoom();
int testClientDataWrapperGetRoomList();
int testClientDataWrapperCreateEntityReply();
int testClientDataWrapperCreateEntityRequest();
int testClientDataWrapperJoinCreateRoomReply();
int testClientDataWrapperComponentSync();
int testClientDataWrapperDestroyEntity();

int testClientNetworkManagerJoinRoom();
int testClientNetworkManagerGetRoomList();
int testClientNetworkManagerCreateEntityReply();
int testClientNetworkManagerCreateEntityRequest();
int testClientNetworkManagerJoinCreateRoomReply();
int testClientNetworkManagerComponentSync();
int testClientNetworkManagerDestroyEntity();

#endif // R_TYPE_CLIENTTEST_HPP