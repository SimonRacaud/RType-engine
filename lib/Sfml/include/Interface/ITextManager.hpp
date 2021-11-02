/*
** PERSONAL PROJECT, 2021
** ITextManager
** File description:
** ITextManager.hpp
*/

#ifndef ITEXTMANAGER_HPP
#define ITEXTMANAGER_HPP

#include <string>
#include "IMovable.hpp"
#include "IDrawable.hpp"
#include "IResizable.hpp"
#include "Item/vector2D.hpp"

template <typename renderTool>
class ITextManager: public IMovable, public IResizable, public IDrawable<renderTool>
{
    public:
        enum class color_e
        {
            RED,
            BLUE,
            GREEN,
            BLACK,
            WHITE,
            MAX_VALUE
        };
    public:
        ~ITextManager() = default;
        // GLOBAL
        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setColor(const color_e &) = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setContent(const std::string &) = 0;

        virtual void draw(renderTool &render) = 0;
        // TOOLS
        virtual void refresh() = 0;
};

#endif