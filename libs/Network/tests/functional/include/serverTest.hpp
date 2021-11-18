/*
** EPITECH PROJECT, 2021
** serverTest.hpp
** File description:
** prototypes of test functions, server side
*/
#ifndef R_TYPE_SERVERTEST_HPP
#define R_TYPE_SERVERTEST_HPP

class intWrapperTCPserver {
  public:
    intWrapperTCPserver() = default;
    explicit intWrapperTCPserver(int val) : _val(val){};
    ~intWrapperTCPserver() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapperTCPserver);
    }

    [[nodiscard]] int getVal() const
    {
        return _val;
    }
    [[nodiscard]] int getOtherVal() const
    {
        return _otherVal;
    }

    [[nodiscard]] uint8_t *serialize() const
    {
        auto data(new uint8_t[sizeof(intWrapperTCPserver)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }
    intWrapperTCPserver(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapperTCPserver)) {
            return;
        }
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{222};
    int _otherVal{444};
};

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

int testUDPserverDisconnection();
int testTCPserverDisconnection();

#endif // R_TYPE_SERVERTEST_HPP