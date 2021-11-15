/*
** EPITECH PROJECT, 2021
** testTramBuffer.cpp
** File description:
** Test Tram buffer
*/

#include <Tram/JoinCreateRoomReply.hpp>
#include <Tram/Serializable.hpp>
#include "Tram/TramBuffer.hpp"
#include "independentTest.hpp"

int testTramBufferComplete()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::TramBuffer myBuffer;

    myBuffer.SetData(myData.serialize(), myData.length());
    if (!myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBufferIncomplete()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    std::size_t truncatedSize(myData.length() / 2);
    auto *truncatedSerializedData(new uint8_t[truncatedSize]);
    memcpy(truncatedSerializedData, serializedData, truncatedSize);

    myBuffer.SetData(truncatedSerializedData, truncatedSize);
    if (myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBufferTruncatedSet()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    std::size_t truncatedSize(myData.length() / 2);
    auto *truncatedSerializedData(new uint8_t[truncatedSize]);
    memcpy(truncatedSerializedData, serializedData, truncatedSize);

    myBuffer.SetData(truncatedSerializedData, truncatedSize);
    myBuffer.SetData(serializedData + truncatedSize, myData.length() - truncatedSize);
    if (!myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBuffer2Sets()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    auto *serializedDataTwice(new uint8_t[(myData.length() * 2)]);
    memcpy(serializedDataTwice, serializedData, myData.length());
    memcpy(serializedDataTwice + myData.length(), serializedData, myData.length());

    myBuffer.SetData(serializedDataTwice, (myData.length() * 2));
    if (!myBuffer.isTramComplete())
        return 84;
    if (!myBuffer.receiveTram())
        return 84;
    if (!myBuffer.isTramComplete())
        return 84;
    if (!myBuffer.receiveTram())
        return 84;
    return 0;
}