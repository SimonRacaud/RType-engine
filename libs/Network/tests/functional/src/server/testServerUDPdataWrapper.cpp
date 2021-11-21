/*
** EPITECH PROJECT, 2021
** testServerUDPdataWrapper.cpp
** File description:
** test network UDP connection with data wrapper server side
*/

#include <cstring>
#include "Asio/AsioConnectionUDP.hpp"
#include "Data/DataWrapping/DataWrapper.hpp"
#include "Network/Tram/JoinRoom.hpp"
#include "Test.hpp"
#include <unordered_map>

using namespace Network;

static DataWrapper startServerGetData()
{
    const std::size_t portServer(8080);
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> recvData;
    AsioConnectionUDP<DataWrapper> server(portServer);

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            return std::get<0>(recvData);
        }
    }
    exit(84);
}
/**
 * @brief Test
 *  AsioConnectionUDP::startAccept()
 *  AsioConnectionUDP::receiveAny()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testUDPserverDataWrapperJoinRoom()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::JoinRoom my_data(my_wrapper.serialize());

    if (my_data.roomId == 51) {
        return 0;
    }
    return 84;
}

int testUDPserverDataWrapperGetRoomList()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::GetRoomList my_data{my_wrapper.serialize()};

    if (my_data.nbItem == 2 && my_data.list[0] == 222 && my_data.list[1] == 444) {
        return 0;
    }
    return 84;
}

int testUDPserverDataWrapperCreateEntityReply()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::CreateEntityReply my_data{my_wrapper.serialize()};

    if (my_data.roomId == 123 && my_data.accept == true && my_data.entityId == 456 && my_data.networkId == 789) {
        return 0;
    }
    return 84;
}

int testUDPserverDataWrapperCreateEntityRequest()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::CreateEntityRequest my_data{my_wrapper.serialize()};

    if (my_data.roomId == 123 && my_data.id == 456 && std::string(my_data.entityType) == std::string("789")
        && my_data.timestamp == 321) {
        return 0;
    }
    return 84;
}

int testUDPserverDataWrapperJoinCreateRoomReply()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::JoinCreateRoomReply my_data{my_wrapper.serialize()};

    if (my_data.accept == true && my_data.roomId == 123456789 && my_data.startTimestamp == 987) {
        return 0;
    }
    return 84;
}

int testUDPserverDataWrapperComponentSync()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::ComponentSync sync(my_wrapper.serialize());
    Time time = (Time) 424242;
    auto type = std::type_index(typeid(TestComponent));
    const size_t compSize = sizeof(TestComponent);
    auto component((TestComponent *) sync.component);

    std::cout << " sync.roomId : " << sync.roomId << std::endl;
    if (sync.roomId != 43)
        return 84;
    std::cout << " sync.networkId : " << sync.networkId << std::endl;
    if (sync.networkId != 42)
        return 84;
    std::cout << " sync.timestamp : " << sync.timestamp << std::endl;
    if (sync.timestamp != time)
        return 84;
    std::cout << " sync.componentType : " << sync.componentType << std::endl;
    if (sync.componentType != type.hash_code())
        return 84;
    std::cout << " sync.componentSize : " << sync.componentSize << std::endl;
    if (sync.componentSize != compSize)
        return 84;
    std::cout << " component->_number : " << component->_number << std::endl;
    if (component->_number != 753951)
        return 84;
    return 0;
}

int testUDPserverDataWrapperDestroyEntity()
{
    DataWrapper my_wrapper(startServerGetData());
    Tram::DestroyEntity my_data{my_wrapper.serialize()};

    if (my_data.roomId == 987654321 && my_data.networkId == 665544) {
        return 0;
    }
    return 84;
}