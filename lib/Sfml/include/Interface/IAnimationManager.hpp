/*
** PERSONAL PROJECT, 2021
** IAnimationManager
** File description:
** IAnimationManager.hpp
*/

#ifndef IANIMATIONMANAGER_HPP
#define IANIMATIONMANAGER_HPP

#include "IMovable.hpp"
#include "IDrawable.hpp"
#include "IResizable.hpp"
#include "Item/vector2D.hpp"
#include <string>

template <typename renderTool>
class IAnimationManager: public IMovable, public IResizable, public IDrawable<renderTool>
{
    public:
        ~IAnimationManager() = default;

        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setDirFilepath(const std::string &) = 0;

        virtual void draw(renderTool &render) = 0;

        virtual void refresh() = 0;
};

#endif