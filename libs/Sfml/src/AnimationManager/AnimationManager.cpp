/*
** PERSONAL PROJECT, 2021
** AnimationManager
** File description:
** AnimationManager.cpp
*/

#include "AnimationManager.hpp"
#include "WindowManager/WindowManager.hpp"

AnimationManager::AnimationManager()
    : _pos(), _size(), _path(), _sprite(nullptr), _texture(nullptr),
      _offset(), _focus(), _nb(0), _limiter(10, AnimationManager::stepManager),
      _func(AnimationManager::defaultMove)
{
}

AnimationManager::AnimationManager(const AnimationManager &src)
    : _pos(src._pos), _size(src._size), _path(src._path), _sprite(src._sprite),
      _texture(src._texture), _offset(src._offset), _focus(src._focus),
      _nb(src._nb), _limiter(10, AnimationManager::stepManager),
      _func(AnimationManager::defaultMove)
{
}

AnimationManager::~AnimationManager()
{
    if (this->_texture)
        this->_texture.reset();
    if (this->_sprite)
        this->_sprite.reset();
}

const vector2f &AnimationManager::getScale()
{
    return this->_size;
}

const vector2D &AnimationManager::getPosition()
{
    return this->_pos;
}

void AnimationManager::setScale(const vector2f &scale)
{
    this->_size = scale;
}

void AnimationManager::setPosition(const vector2D &pos)
{
    this->_pos = pos;
}

void AnimationManager::setSrcPath(const std::string &path)
{
    this->_path = path;
}

void AnimationManager::draw(renderToolSfml &render)
{
    if (!this->_sprite || !this->_texture)
        this->refresh();
    if (_windowTmp == nullptr)
        _windowTmp = dynamic_cast<WindowManager *>(render.get());
    _windowTmp->_window->draw(this->getNextSprite());
}

void AnimationManager::refresh()
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

void AnimationManager::setFocus(const surface &focus)
{
    this->_focus = focus;
}

void AnimationManager::forceOffset(size_t offset)
{
    this->_offset = offset;
}

void AnimationManager::setNbMember(size_t nb)
{
    this->_nb = nb;
}

const sf::Drawable &AnimationManager::getNextSprite()
{
    this->_limiter.runIt(this->_offset);
    if (this->_offset >= this->_nb)
        this->_offset = 0;

    surface tmp = this->_func(this->_focus, this->_offset);
    size_t size_x = tmp.size.x;
    size_t size_y = tmp.size.y;
    size_t x = tmp.pos.x;
    size_t y = tmp.pos.y;


    this->_sprite->setTextureRect(sf::IntRect(x, y, size_x, size_y));
    return *(this->_sprite.get());
}

void AnimationManager::stepManager(size_t &step)
{
    step++;
}

void AnimationManager::setStepMovement(std::function<surface (surface, size_t)> func)
{
    if (func)
        this->_func = func;
    else
        this->_func = nullptr;
}

surface AnimationManager::defaultMove(surface focus, size_t offset)
{
    size_t size_x = focus.size.x;
    size_t size_y = focus.size.y;
    size_t x = focus.pos.x + size_x * offset;
    size_t y = focus.pos.y;

    return surface(vector2D(x, y), vector2D(size_x, size_y));
}