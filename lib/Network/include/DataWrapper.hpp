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
#include <type_traits>

#include "Tram/ComponentSync.hpp"
#include "Tram/CreateEntityReply.hpp"
#include "Tram/CreateEntityRequest.hpp"
#include "Tram/DestroyEntity.hpp"
#include "Tram/GetRoomList.hpp"
#include "Tram/JoinCreateRoomReply.hpp"
#include "Tram/JoinRoom.hpp"
#include "Tram/header.hpp"

class DataWrapper : public IDataWrapper {
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

    //    DataWrapper *operator&() const;
    //    DataWrapper &operator*() const override;
    [[nodiscard]] std::size_t size() const override;

    template <Pointerable Data> void setData(Data &dataToSet);

    [[nodiscard]] Tram::TramType getDataType() const;
    template <Pointerable Data> Data getData();

  private:
    DataType _data;
};

// DataWrapper *DataWrapper::operator&() const
// {
// }

// DataWrapper &DataWrapper::operator*() const
// {
// }

inline std::size_t DataWrapper::size() const
{
    return sizeof(DataWrapper);
}

template <Pointerable Data> void DataWrapper::setData(Data &dataToSet)
{
    _data = std::forward<Data>(dataToSet);
}

template <Pointerable Data> [[nodiscard]] Data DataWrapper::getData()
{
    return std::get<Data>(_data);
}

[[nodiscard]] inline Tram::TramType DataWrapper::getDataType() const
{
    std::visit(
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
    return Tram::TramType::JOIN_ROOM_REPLY;
}

#endif // R_TYPE_DATAWRAPPER_HPP