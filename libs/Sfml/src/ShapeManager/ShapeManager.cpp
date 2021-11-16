/*
** PERSONAL PROJECT, 2021
** ShapeManager
** File description:
** ShapeManager.cpp
*/

#include "ShapeManager.hpp"
#include "ColorLink/ColorLink.hpp"
#include "WindowManager/WindowManager.hpp"

ShapeManager::ShapeManager() : _pos(), _size(), _color(color_e::WHITE), _shape(nullptr)
{
}

ShapeManager::ShapeManager(const ShapeManager &src) : _pos(src._pos), _size(src._size), _color(src._color), _shape(src._shape)
{
}

ShapeManager::ShapeManager(const vector2D &pos, const vector2D &size, color_e color) : _pos(pos), _size(size), _color(color), _shape(nullptr)
{
}

const vector2D &ShapeManager::getSize()
{
    return this->_size;
}

const vector2D &ShapeManager::getPosition()
{
    return this->_pos;
}

void ShapeManager::setSize(const vector2D &size)
{
    this->_size = size;
}

void ShapeManager::setPosition(const vector2D &pos)
{
    this->_pos = pos;
    if (_shape)
        this->_shape->setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
}

void ShapeManager::setColors(const color_e &color)
{
    this->_color = color;
}

void ShapeManager::draw()
{
    if (!this->_shape)
        this->refresh();
    WindowManager::_window->draw(*(this->_shape.get()));
}

void ShapeManager::refresh()
{
    if (!this->_shape)
        this->_shape = std::make_shared<sf::RectangleShape>();
    this->_shape->setFillColor(ColorLink::getColor(this->_color));
    this->_shape->setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
    this->_shape->setSize(sf::Vector2f(this->_size.x, this->_size.y));
}