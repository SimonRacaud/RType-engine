/*
** PERSONAL PROJECT, 2021
** IShapeManager
** File description:
** IShapeManager.hpp
*/

#ifndef ISHAPEMANAGER_HPP
#define ISHAPEMANAGER_HPP

#include "color.hpp"
#include "IMovable.hpp"
#include "IDrawable.hpp"
#include "IResizable.hpp"
#include "Item/surface.hpp"

template <typename renderTool>
class IShapeManager: public IMovable, public IResizable, public IDrawable<renderTool>
{
    public:
        ~IShapeManager() = default;
        // GLOBAL
        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;

        virtual void setColors(const color_e &) = 0;

        virtual void draw(renderTool &render) = 0;
        // TOOLS
        virtual void refresh() = 0;
};

#endif