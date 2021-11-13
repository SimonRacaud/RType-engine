/*
** EPITECH PROJECT, 2021
** IDataWrapper.hpp
** File description:
** Interface for data wrapper class
*/
#ifndef R_TYPE_IDATAWRAPPER_HPP
#define R_TYPE_IDATAWRAPPER_HPP

#include "utils/Concepts/Pointerable.hpp"

class IDataWrapper {
    // todo requires Pointerable
  public:
    //    virtual IDataWrapper *operator&() const = 0;
    //    virtual IDataWrapper &operator*() const = 0;
    [[nodiscard]] virtual std::size_t length() const = 0;

    //    template <Pointerable Data>
    //    virtual void setData() = 0;
};

#endif // R_TYPE_IDATAWRAPPER_HPP