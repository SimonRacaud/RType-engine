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
  public:
    [[nodiscard]] virtual std::size_t length() const = 0;
};

#endif // R_TYPE_IDATAWRAPPER_HPP