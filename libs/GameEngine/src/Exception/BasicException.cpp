/*
** EPITECH PROJECT , 2021
** BasicException
** File description:
** simon
*/

#include "Exception/BasicException.hpp"

Engine::BasicException::BasicException(const std::string &message)
    : _message(message)
{}

const char *Engine::BasicException::what() const noexcept
{
    return _message.c_str();
}
