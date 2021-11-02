/*
** PERSONAL PROJECT, 2021
** IAnimationManager
** File description:
** IAnimationManager.hpp
*/

#ifndef IANIMATIONMANAGER_HPP
#define IANIMATIONMANAGER_HPP

#include "Item/vector2D.hpp"
#include <string>

class IAnimationManager
{
    public:
        ~IAnimationManager() = default;

        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setDirFilepath(const std::string &) = 0;

        virtual void refresh() = 0;
};

#endif