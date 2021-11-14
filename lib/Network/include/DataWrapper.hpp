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
  public:
    DataWrapper() = default;
    ~DataWrapper() = default;

    explicit DataWrapper(const uint8_t *data, std::size_t length);

    virtual uint8_t *serialize() const;
    virtual void deserialize(const uint8_t *data, std::size_t length);
    [[nodiscard]] std::size_t length() const override;

  private:
    std::size_t _dataLength{0};
    uint8_t *_data{nullptr};
};

#endif // R_TYPE_DATAWRAPPER_HPP