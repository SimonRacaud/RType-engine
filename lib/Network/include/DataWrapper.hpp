/*
** EPITECH PROJECT, 2021
** DataWrapper.hpp
** File description:
** Wraps data to be sent on network
*/

#ifndef R_TYPE_DATAWRAPPER_HPP
#define R_TYPE_DATAWRAPPER_HPP

#include <variant>
#include "IDataWrapper.hpp"
//#include "ISerializable.hpp"
#include <type_traits>

#include "Tram/ComponentSync.hpp"
#include "Tram/CreateEntityReply.hpp"
#include "Tram/CreateEntityRequest.hpp"
#include "Tram/DestroyEntity.hpp"
#include "Tram/GetRoomList.hpp"
#include "Tram/JoinCreateRoomReply.hpp"
#include "Tram/JoinRoom.hpp"
#include "Tram/header.hpp"

class DataWrapper : public IDataWrapper /*, public Network::ISerializable*/ {
    // todo union ?
    //  more optimized in memory
    //  less safe

    // https://www.youtube.com/watch?v=AFsALrqFy_Q]
    // min 9'40

    // std::monostate
    using DataType = std::variant<std::monostate, Tram::ComponentSync, Tram::CreateEntityReply,
        Tram::CreateEntityRequest, Tram::DestroyEntity, Tram::GetRoomList, Tram::JoinCreateRoomReply, Tram::JoinRoom>;

  public:
    DataWrapper() = default;
    ~DataWrapper() = default;

    DataWrapper(uint8_t *data);
    DataWrapper &operator=(uint8_t *data);
    DataWrapper(DataWrapper &rhs);
    DataWrapper &operator=(const DataWrapper &rhs);
    DataWrapper &operator=(DataWrapper &&rhs) noexcept;

    virtual uint8_t *serialize();
    //    virtual void deserialize(uint8_t *buffer);
    [[nodiscard]] std::size_t length() const override;

    template <Pointerable Data> void setData(Data &dataToSet);
    template <Pointerable Data> void setData(Data &&dataToSet) noexcept;
    void setData();

    [[nodiscard]] Tram::TramType getDataType() const;
    template <Pointerable Data> [[nodiscard]] Data getData() const;
    //    template <Pointerable Data> [[nodiscard]] Data getData(Tram::TramType type) const;

  private:
    DataType _data{std::monostate()};
    std::size_t _dataLength{0};
};

// DataWrapper *DataWrapper::operator&() const
// {
// }

// DataWrapper &DataWrapper::operator*() const
// {
// }

inline std::size_t DataWrapper::length() const
{
    return _dataLength;

    //    return sizeof(DataWrapper);
}

template <Pointerable Data> void DataWrapper::setData(Data &dataToSet)
{
    _dataLength = dataToSet.length();
    _data = std::forward<Data>(dataToSet);
}
template <Pointerable Data> void DataWrapper::setData(Data &&dataToSet) noexcept
{
    _dataLength = dataToSet.length();
    _data = std::forward<Data>(dataToSet);
}

inline void DataWrapper::setData()
{
    _dataLength = 0;
    _data = std::monostate();
}

template <Pointerable Data> [[nodiscard]] Data DataWrapper::getData() const
{
    return std::get<Data>(_data);
}

[[nodiscard]] inline Tram::TramType DataWrapper::getDataType() const
{
    return std::visit(
        [](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if constexpr (std::is_same_v<T, Tram::ComponentSync>) {
                return Tram::TramType::SYNC_COMPONENT;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityReply>) {
                return Tram::TramType::CREATE_ENTITY_REPLY;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityRequest>) {
                return Tram::TramType::CREATE_ENTITY;
            } else if constexpr (std::is_same_v<T, Tram::JoinCreateRoomReply>) {
                return Tram::TramType::JOIN_ROOM_REPLY;
            } else if constexpr (std::is_same_v<T, Tram::DestroyEntity>) {
                return Tram::TramType::DESTROY_ENTITY;
            } else if constexpr (std::is_same_v<T, Tram::GetRoomList>) {
                return Tram::TramType::GET_ROOM_LIST;
            } else if constexpr (std::is_same_v<T, Tram::JoinRoom>) {
                return Tram::TramType::JOIN_ROOM;
            }
            return Tram::TramType::NONE;
        },
        _data);
}

DataWrapper::DataWrapper(DataWrapper &rhs)
{
    //    Tram::TramType type(rhs.getDataType());

    //    _data = rhs.getData<type>();

    std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if constexpr (std::is_same_v<T, Tram::ComponentSync>) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityReply>) {
                _data = rhs.getData<Tram::CreateEntityReply>();
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityRequest>) {
                _data = rhs.getData<Tram::CreateEntityRequest>();
            } else if constexpr (std::is_same_v<T, Tram::JoinCreateRoomReply>) {
                _data = rhs.getData<Tram::JoinCreateRoomReply>();
            } else if constexpr (std::is_same_v<T, Tram::DestroyEntity>) {
                _data = rhs.getData<Tram::DestroyEntity>();
            } else if constexpr (std::is_same_v<T, Tram::GetRoomList>) {
                _data = rhs.getData<Tram::GetRoomList>();
            } else if constexpr (std::is_same_v<T, Tram::JoinRoom>) {
                _data = rhs.getData<Tram::JoinRoom>();
            }
            return Tram::TramType::NONE;
        },
        _data);
}
DataWrapper &DataWrapper::operator=(const DataWrapper &rhs)
{
    std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if constexpr (std::is_same_v<T, Tram::ComponentSync>) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityReply>) {
                _data = rhs.getData<Tram::CreateEntityReply>();
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityRequest>) {
                _data = rhs.getData<Tram::CreateEntityRequest>();
            } else if constexpr (std::is_same_v<T, Tram::JoinCreateRoomReply>) {
                _data = rhs.getData<Tram::JoinCreateRoomReply>();
            } else if constexpr (std::is_same_v<T, Tram::DestroyEntity>) {
                _data = rhs.getData<Tram::DestroyEntity>();
            } else if constexpr (std::is_same_v<T, Tram::GetRoomList>) {
                _data = rhs.getData<Tram::GetRoomList>();
            } else if constexpr (std::is_same_v<T, Tram::JoinRoom>) {
                _data = rhs.getData<Tram::JoinRoom>();
            }
            return Tram::TramType::NONE;
        },
        _data);
    return *this;
}
DataWrapper &DataWrapper::operator=(DataWrapper &&rhs) noexcept
{
    std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if constexpr (std::is_same_v<T, Tram::ComponentSync>) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityReply>) {
                _data = rhs.getData<Tram::CreateEntityReply>();
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityRequest>) {
                _data = rhs.getData<Tram::CreateEntityRequest>();
            } else if constexpr (std::is_same_v<T, Tram::JoinCreateRoomReply>) {
                _data = rhs.getData<Tram::JoinCreateRoomReply>();
            } else if constexpr (std::is_same_v<T, Tram::DestroyEntity>) {
                _data = rhs.getData<Tram::DestroyEntity>();
            } else if constexpr (std::is_same_v<T, Tram::GetRoomList>) {
                _data = rhs.getData<Tram::GetRoomList>();
            } else if constexpr (std::is_same_v<T, Tram::JoinRoom>) {
                _data = rhs.getData<Tram::JoinRoom>();
            }
            return Tram::TramType::NONE;
        },
        _data);
    rhs.setData();
    return *this;
}

DataWrapper &DataWrapper::operator=(uint8_t *data)
{
    Tram::header dataHeader(data);

    std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if (dataHeader.type == Tram::TramType::SYNC_COMPONENT) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if (dataHeader.type == Tram::TramType::CREATE_ENTITY_REPLY) {
                //                _data = Tram::CreateEntityReply(data); // todo copy constructor ?
                _data.emplace<Tram::CreateEntityReply>(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::CREATE_ENTITY) {
                //                _data = Tram::CreateEntityRequest(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::JOIN_ROOM_REPLY) {
                //                _data = Tram::JoinCreateRoomReply(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::DESTROY_ENTITY) {
                //                _data = Tram::DestroyEntity(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::GET_ROOM_LIST) {
                //                _data = Tram::GetRoomList(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::JOIN_ROOM) {
                //                _data = Tram::JoinRoom(data); // todo copy constructor ?
            }
        },
        _data);
    return *this;
}

DataWrapper::DataWrapper(uint8_t *data)
{
    Tram::header dataHeader(data);

    std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if (dataHeader.type == Tram::TramType::SYNC_COMPONENT) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if (dataHeader.type == Tram::TramType::CREATE_ENTITY_REPLY) {
                _data = Tram::CreateEntityReply(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::CREATE_ENTITY) {
                //                _data = Tram::CreateEntityRequest(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::JOIN_ROOM_REPLY) {
                //                _data = Tram::JoinCreateRoomReply(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::DESTROY_ENTITY) {
                //                _data = Tram::DestroyEntity(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::GET_ROOM_LIST) {
                //                _data = Tram::GetRoomList(data); // todo copy constructor ?
            } else if (dataHeader.type == Tram::TramType::JOIN_ROOM) {
                //                _data = Tram::JoinRoom(data); // todo copy constructor ?
            }
        },
        _data);
}

inline uint8_t *DataWrapper::serialize()
{
    if (_data.index() == 0) {
        return nullptr;
    }
    return std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if constexpr (std::is_same_v<T, Tram::ComponentSync>) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityReply>) {
                return reinterpret_cast<Tram::CreateEntityReply>(_data).serialize();
            } else if constexpr (std::is_same_v<T, Tram::CreateEntityRequest>) {
                //                return Tram::CreateEntityRequest::serialize();
            } else if constexpr (std::is_same_v<T, Tram::JoinCreateRoomReply>) {
                //                return Tram::JoinCreateRoomReply::serialize();
            } else if constexpr (std::is_same_v<T, Tram::DestroyEntity>) {
                //                return Tram::DestroyEntity::serialize();
            } else if constexpr (std::is_same_v<T, Tram::GetRoomList>) {
                //                return Tram::GetRoomList::serialize();
            } else if constexpr (std::is_same_v<T, Tram::JoinRoom>) {
                //                return Tram::JoinRoom::serialize();
            }
            return nullptr;
        },
        _data);
}
// void DataWrapper::deserialize(uint8_t *buffer)
//{
// }
/*

template <Pointerable Data> Data DataWrapper::getData(Tram::TramType type) const
{
    return std::visit(
        [&](const auto &actData) {
            using T = std::decay_t<decltype(actData)>;

            if (type == Tram::ComponentSync) {
                //                _data = rhs.getData<Tram::ComponentSync>();
                std::cout << "hello" << std::endl;
            } else if (type == Tram::TramType::SYNC_COMPONENT) {
                return getData<Tram::CreateEntityReply>();
            } else if (type == Tram::TramType::CREATE_ENTITY_REPLY) {
                return getData<Tram::CreateEntityRequest>();
            } else if (type == Tram::TramType::CREATE_ENTITY) {
                return getData<Tram::JoinCreateRoomReply>();
            } else if (type == Tram::TramType::JOIN_ROOM_REPLY) {
                return getData<Tram::DestroyEntity>();
            } else if (type == Tram::TramType::DESTROY_ENTITY) {
                return getData<Tram::GetRoomList>();
            } else if (type == Tram::TramType::GET_ROOM_LIST) {
                return getData<Tram::JoinRoom>();
            }
            return Tram::TramType::NONE;
        },
        _data);
}
*/

#endif // R_TYPE_DATAWRAPPER_HPP