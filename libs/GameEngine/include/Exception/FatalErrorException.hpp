/*
** EPITECH PROJECT , 2021
** FatalErrorException
** File description:
** simon
*/

#ifndef FATALERROREXCEPTION_HPP
#define FATALERROREXCEPTION_HPP

#include "BasicException.hpp"

namespace Engine {
    class FatalErrorException : public BasicException {
        FatalErrorException(std::string const &message = "Fatal error")
            : BasicException(message) {}
        virtual ~FatalErrorException() = default;
    };
}

#endif // FATALERROREXCEPTION_HPP
