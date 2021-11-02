/*
** PERSONAL PROJECT, 2021
** IWindowManager
** File description:
** IWindowManager.hpp
*/

#ifndef IWINDOWMANAGER_HPP
#define IWINDOWMANAGER_HPP

#include <string>
#include "Item/vector2D.hpp"

class IWindowManager
{
    public:
        ~IWindowManager() = default;

        virtual void setFrameLiminter(size_t) = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setName(const std::string &) = 0;

        virtual bool isOpen() const = 0;

        virtual void open() = 0;
        virtual void clear() = 0;
        virtual void refresh() = 0;
        virtual void close() = 0;
};

#endif