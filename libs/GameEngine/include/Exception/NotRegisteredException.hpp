/*
** EPITECH PROJECT , 2021
** FatalErrorException
** File description:
** simon
*/

#ifndef NOTREGISTEREDEXCEPTION_HPP
#define NOTREGISTEREDEXCEPTION_HPP

#include "BasicException.hpp"
#include "global.hpp"

namespace Engine
{
    class NotRegisteredException : public BasicException {
      public:
        NotRegisteredException(std::string const &type, Index index)
            : BasicException(
                type + " " + std::to_string(index) + " not registered")
        {
        }

        explicit NotRegisteredException(std::string const &type)
            : BasicException(type + " not registered")
        {
        }

        virtual ~NotRegisteredException() = default;
    };
} // namespace Engine

#endif // NOTREGISTEREDEXCEPTION_HPP
