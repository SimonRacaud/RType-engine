/*
** EPITECH PROJECT , 2021
** RuntimeException
** File description:
** simon
*/

#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include "BasicException.hpp"

namespace Engine {
    class RuntimeException : public BasicException {
      public:
        RuntimeException(std::string const &message = "Runtime error")
            : BasicException(message) {}

        virtual ~RuntimeException() = default;
    };
}

#endif // RUNTIMEEXCEPTION_HPP
