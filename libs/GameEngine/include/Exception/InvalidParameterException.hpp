/*
** EPITECH PROJECT , 2021
** InvalidParameterException
** File description:
** simon
*/

#ifndef INVALIDPARAMETEREXCEPTION_HPP
#define INVALIDPARAMETEREXCEPTION_HPP

#include "BasicException.hpp"

namespace Engine {
    class InvalidParameterException : public BasicException {
      public:
        InvalidParameterException(std::string const &message = "Invalid parameter")
            : BasicException(message) {}
        virtual ~InvalidParameterException() = default;
    };
}

#endif // INVALIDPARAMETEREXCEPTION_HPP
