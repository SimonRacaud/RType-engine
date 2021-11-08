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
#include "Item/surface.hpp"
#include "Item/vector2D.hpp"
#include <string>
#include <functional>

template <typename renderTool>
class IAnimationManager: public IMovable, public IResizable, public IDrawable<renderTool>
{
    public:
        ~IAnimationManager() = default;

        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setSrcPath(const std::string &) = 0;

        virtual void draw(renderTool &render) = 0;

        virtual void refresh() = 0;

        virtual void setNbMember(size_t) = 0;
        virtual void forceOffset(size_t) = 0;
        virtual void setFocus(const surface &) = 0;
        virtual void setStepMovement(std::function<surface (surface, size_t)>) = 0;
};

#endif