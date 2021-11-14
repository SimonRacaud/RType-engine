/*
** PERSONAL PROJECT, 2021
** ITextManager
** File description:
** ITextManager.hpp
*/

#ifndef ITEXTMANAGER_HPP
#define ITEXTMANAGER_HPP

#include <string>
#include "color.hpp"
#include "IDrawable.hpp"
#include "Item/vector2D.hpp"

class ITextManager: public IDrawable
{
    public:
        ~ITextManager() = default;
        // GLOBAL
        virtual const vector2D &getSize() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setColor(const color_e &) = 0;
        virtual void setSize(const vector2D &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setContent(const std::string &) = 0;
        virtual void setFont(const std::string &) = 0;

        virtual void draw() = 0;
        // TOOLS
        virtual void refresh() = 0;
};

#endif