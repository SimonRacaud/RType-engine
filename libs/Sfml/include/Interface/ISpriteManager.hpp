/*
** PERSONAL PROJECT, 2021
** ISpriteManager
** File description:
** ISpriteManager.hpp
*/

#ifndef ISPRITEMANAGER_HPP
#define ISPRITEMANAGER_HPP

#include <string>
#include "IMovable.hpp"
#include "IDrawable.hpp"
#include "IResizable.hpp"
#include "Item/surface.hpp"
#include "Item/vector2f.hpp"

template <typename renderTool>
class ISpriteManager: public IDrawable<renderTool>
{
    public:
        ~ISpriteManager() = default;
        // GLOBAL
        virtual const vector2f &getScale() = 0;
        virtual const vector2D &getPosition() = 0;
        virtual void setScale(const vector2f &) = 0;
        virtual void setPosition(const vector2D &) = 0;
        virtual void setSrcFilepath(const std::string &) = 0;

        virtual void draw() = 0;
        // TOOLS
        virtual void refresh() = 0;
};

#endif