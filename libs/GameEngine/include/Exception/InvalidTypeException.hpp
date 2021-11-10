/*
** EPITECH PROJECT , 2021
** InvalidTypeException
** File description:
** simon
*/

#ifndef INVALIDTYPEEXCEPTION_HPP
#define INVALIDTYPEEXCEPTION_HPP

#include "BasicException.hpp"

namespace Engine {
    class InvalidTypeException : public BasicException {
      public:
        InvalidTypeException(std::string const &message = "Invalid type error")
            : BasicException(message) {}
        virtual ~InvalidTypeException() = default
    };
}

#endif // INVALIDTYPEEXCEPTION_HPP
