/*
** PERSONAL PROJECT, 2021
** SpriteManager
** File description:
** SpriteManager.cpp
*/

#include "SpriteManager.hpp"
#include "WindowManager/WindowManager.hpp"

SpriteManager::SpriteManager()
    : _pos(), _size(), _path(), _sprite(nullptr), _texture(nullptr)
{
}

SpriteManager::SpriteManager(vector2D pos, vector2f scale, std::string path)
    : _pos(pos), _size(scale), _path(path), _sprite(nullptr), _texture(nullptr)
{
}

SpriteManager::SpriteManager(const SpriteManager &src)
    : _pos(src._pos), _size(src._size), _path(src._path), _sprite(src._sprite),
      _texture(src._texture)
{
}

SpriteManager::~SpriteManager()
{
    if (this->_texture)
        this->_texture.reset();
    if (this->_sprite)
        this->_sprite.reset();
}

const vector2f &SpriteManager::getScale()
{
    return this->_size;
}

const vector2D &SpriteManager::getPosition()
{
    return this->_pos;
}

void SpriteManager::setScale(const vector2f &scale)
{
    this->_size = scale;
}

void SpriteManager::setPosition(const vector2D &pos)
{
    this->_pos = pos;
}

void SpriteManager::setSrcFilepath(const std::string &path)
{
    this->_path = path;
}

void SpriteManager::draw()
{
    if (!this->_sprite || !this->_texture)
        this->refresh();
    WindowManager::_window->draw(*(this->_sprite.get()));
}

void SpriteManager::refresh()
{
    if (!this->_sprite)
        this->_sprite = std::make_shared<sf::Sprite>();
    if (!this->_texture)
        this->_texture = std::make_shared<sf::Texture>();
    if (!this->_texture->loadFromFile(this->_path))
        throw std::invalid_argument("Texture load failed " + this->_path);
    this->_sprite->setTexture(*(this->_texture.get()));
    this->_sprite->setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
    if (this->_size.x && this->_size.y)
        this->_sprite->setScale(sf::Vector2f(this->_size.x, this->_size.y));
}

void SpriteManager::setSize(const vector2D &)
{
    throw std::invalid_argument("Not already dev");
}

const vector2D &SpriteManager::getSize()
{
    throw std::invalid_argument("Not already dev");
}