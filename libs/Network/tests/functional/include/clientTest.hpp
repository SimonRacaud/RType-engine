/*
** EPITECH PROJECT, 2021
** clientTest.hpp
** File description:
** prototypes of test functions, client side
*/

#ifndef R_TYPE_CLIENTTEST_HPP
#define R_TYPE_CLIENTTEST_HPP

#include <cstring>
class intWrapperTCPclient {
  public:
    intWrapperTCPclient() = default;
    explicit intWrapperTCPclient(int val) : _val(val){};
    ~intWrapperTCPclient() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapperTCPclient);
    }

    [[nodiscard]] int getVal() const
    {
        return _val + _otherVal;
    }

    [[nodiscard]] uint8_t *serialize() const
    {
        auto data(new uint8_t[sizeof(intWrapperTCPclient)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }
    intWrapperTCPclient(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapperTCPclient))
            return;
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{111};
    int _otherVal{333};
};

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
int testTCPclientDisconnection();

#endif // R_TYPE_CLIENTTEST_HPP