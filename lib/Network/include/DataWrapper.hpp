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

struct my_structData {
    int testValue{2};
    static inline std::size_t size()
    {
        return sizeof(my_structData);
    }
};

class DataWrapper : public IDataWrapper {
    using DataType = std::variant<my_structData /*types of data trams*/>;

  public:
    DataWrapper() = default;
    ~DataWrapper() = default;

    //    DataWrapper *operator&() const;
    //    DataWrapper &operator*() const override;
    [[nodiscard]] std::size_t size() const override;

    //    template <Pointerable Data> bool isDataTypeRegistered(Data &data);
    template <Pointerable Data> void setData(Data &dataToSet);

    template <typename Data> Data getData() const;

  private:
  private:
    DataType _data;
};

// DataWrapper *DataWrapper::operator&() const
//{
// }

// DataWrapper &DataWrapper::operator*() const
//{
// }

inline std::size_t DataWrapper::size() const
{
    return sizeof(DataWrapper);
}

// template <typename Data> bool DataWrapper::isDataTypeRegistered(Data &data)
//{
//     for (uint i = 0; i < std::variant_size_v<DataType>; ++i) {
//         if (std::is_same_v<Data, std::variant_alternative_t<i, const DataType>>) {
//             return true;
//         }
//     }
//     return false;
// }

template <Pointerable Data> void DataWrapper::setData(Data &dataToSet)
{
    _data = std::forward<Data>(dataToSet);
}

template <typename Data> [[nodiscard]] Data DataWrapper::getData() const

{
    //        return
    return std::get<Data>(_data);
}

#endif // R_TYPE_DATAWRAPPER_HPP