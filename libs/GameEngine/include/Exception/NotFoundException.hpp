/*
** EPITECH PROJECT , 2021
** NotFoundException
** File description:
** simon
*/

#ifndef NOTFOUNDEXCEPTION_HPP
#define NOTFOUNDEXCEPTION_HPP

#include "BasicException.hpp"

namespace Engine {
    class NotFoundException : public BasicException {
      public:
        NotFoundException(std::string const &message = "Not found error")
            : BasicException(message) {}
        virtual ~NotFoundException() = default;
    };
}

#endif // NOTFOUNDEXCEPTION_HPP
