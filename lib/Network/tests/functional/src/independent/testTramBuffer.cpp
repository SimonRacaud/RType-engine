/*
** EPITECH PROJECT, 2021
** testTramBuffer.cpp
** File description:
** Test Tram buffer
*/

#include <Tram/JoinCreateRoomReply.hpp>
#include <Tram/header.hpp>
#include "Tram/TramBuffer.hpp"
#include "independentTest.hpp"

int testTramBufferComplete()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::header myHeader(Tram::TramType::JOIN_ROOM_REPLY, myData.length());
    Tram::TramBuffer myBuffer;

    myBuffer.SetData(myHeader.serialize(), myHeader.length());
    myBuffer.SetData(myData.serialize(), myData.length());
    if (!myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBufferIncomplete()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::header myHeader(Tram::TramType::JOIN_ROOM_REPLY, myData.length());
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    std::size_t truncatedSize(myData.length() / 2);
    auto *truncatedSerializedData(new uint8_t[truncatedSize]);
    memcpy(truncatedSerializedData, serializedData, truncatedSize);

    myBuffer.SetData(myHeader.serialize(), myHeader.length());
    myBuffer.SetData(truncatedSerializedData, truncatedSize);
    if (myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBufferTruncatedSet()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::header myHeader(Tram::TramType::JOIN_ROOM_REPLY, myData.length());
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    std::size_t truncatedSize(myData.length() / 2);
    auto *truncatedSerializedData(new uint8_t[truncatedSize]);
    memcpy(truncatedSerializedData, serializedData, truncatedSize);

    myBuffer.SetData(myHeader.serialize(), myHeader.length());
    myBuffer.SetData(truncatedSerializedData, truncatedSize);
    myBuffer.SetData(serializedData + truncatedSize, myData.length() - truncatedSize);
    if (!myBuffer.isTramComplete())
        return 84;
    return 0;
}

int testTramBuffer2Sets()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::header myHeader(Tram::TramType::JOIN_ROOM_REPLY, myData.length());
    Tram::TramBuffer myBuffer;
    uint8_t *serializedData(myData.serialize());
    uint8_t *serializedHeader(myHeader.serialize());
    auto *serializedDataTwice(new uint8_t[(myData.length() * 2) + (myHeader.length() * 2)]);
    memcpy(serializedDataTwice, serializedHeader, myHeader.length());
    memcpy(serializedDataTwice + myHeader.length(), serializedData, myData.length());
    memcpy(serializedDataTwice + myHeader.length() + myData.length(), serializedHeader, myHeader.length());
    memcpy(serializedDataTwice + (myHeader.length() * 2) + myData.length(), serializedData, myData.length());

    myBuffer.SetData(serializedDataTwice, (myData.length() * 2) + (myHeader.length() * 2));
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

int testTramBufferCreateBuffer()
{
    Tram::JoinCreateRoomReply myData(true, 12, std::chrono::milliseconds(34));
    Tram::header myHeader(Tram::TramType::JOIN_ROOM_REPLY, myData.length());
    Tram::TramBuffer myBuffer;
    std::size_t myLength(0);
    uint8_t *serializedData(Tram::TramBuffer::createBuff(myHeader, myData, &myLength));

    myBuffer.SetData(serializedData, myLength);
    if (!myBuffer.isTramComplete())
        return 84;
    return 0;
}