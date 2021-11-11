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

#include "Tram/ComponentSync.hpp"
#include "Tram/CreateEntityReply.hpp"
#include "Tram/CreateEntityRequest.hpp"
#include "Tram/DestroyEntity.hpp"
#include "Tram/GetRoomList.hpp"
#include "Tram/JoinCreateRoomReply.hpp"
#include "Tram/JoinRoom.hpp"
#include "Tram/header.hpp"

class DataWrapper : public IDataWrapper {
    using DataType =
        std::variant<Tram::ComponentSync, Tram::CreateEntityReply, Tram::CreateEntityRequest, Tram::JoinCreateRoomReply,
            Tram::DestroyEntity, Tram::GetRoomList, Tram::header, Tram::JoinCreateRoomReply, Tram::JoinRoom>;

  public:
    DataWrapper() = default;
    ~DataWrapper() = default;

    //    DataWrapper *operator&() const;
    //    DataWrapper &operator*() const override;
    [[nodiscard]] std::size_t size() const override;

    template <Pointerable Data> void setData(Data &dataToSet);

    template <Pointerable Data> Data getData() const;

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

template <Pointerable Data> [[nodiscard]] Data DataWrapper::getData() const
{
    return std::get<Data>(_data);
}

#endif // R_TYPE_DATAWRAPPER_HPP