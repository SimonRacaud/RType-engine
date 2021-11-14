/*
** PERSONAL PROJECT, 2021
** ShapeManager
** File description:
** ShapeManager.hpp
*/

#ifndef SHAPEMANAGER_HPP
#define SHAPEMANAGER_HPP

#include "build.hpp"
#include "Interface/IShapeManager.hpp"

class ShapeManager: public IShapeManager
{
    public:
        ShapeManager();
        ShapeManager(const ShapeManager &);
        ShapeManager(const vector2D &pos, const vector2D &size, color_e color);
        ~ShapeManager() = default;
        // GLOBAL
        const vector2D &getSize();
        const vector2D &getPosition();
        void setSize(const vector2D &);
        void setPosition(const vector2D &);

        void setColors(const color_e &);

        void draw();
        // TOOLS
        void refresh();

    private:
        vector2D _pos;
        vector2D _size;
        color_e _color;
        std::shared_ptr<sf::RectangleShape> _shape;
};

#endif