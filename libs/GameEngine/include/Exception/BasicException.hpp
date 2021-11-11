/*
** EPITECH PROJECT , 2021
** BasicException
** File description:
** simon
*/

#ifndef BASICEXCEPTION_HPP
#define BASICEXCEPTION_HPP

#include <exception>
#include <string>

namespace Engine
{
    class BasicException: public std::exception {
      public:
        BasicException(std::string const &message);
        virtual ~BasicException() = default;

        virtual const char *what() const noexcept;

      private:
        const std::string _message;
    };
}

#endif // BASICEXCEPTION_HPP
