/*
** PERSONAL PROJECT, 2021
** WindowManager
** File description:
** WindowManager.cpp
*/

#include "WindowManager.hpp"

WindowManager::WindowManager(): _window(nullptr), _fps(0), _size(0, 0), _name("")
{
}

WindowManager::WindowManager(const WindowManager &src): _window(src._window), _fps(src._fps), _size(src._size), _name(src._name)
{
}

WindowManager::~WindowManager()
{
    if (this->isOpen())
        this->_window->close();
    if (this->_window)
        this->_window.reset();
}

void WindowManager::setFramerateLimiter(size_t fps)
{
    if (this->_window)
        this->_window->setFramerateLimit(fps);
    this->_fps = fps;
}

void WindowManager::setSize(const vector2D &size)
{
    if (this->_window)
        this->_window->setSize(sf::Vector2u(size.x, size.y));
    this->_size = size;
}

void WindowManager::setName(const std::string &name)
{
    if (this->_window)
        this->_window->setTitle(name);
    this->_name = name;
}

bool WindowManager::isOpen() const
{
    return this->_window && this->_window->isOpen();
}

void WindowManager::open()
{
    if (this->_window)
        throw std::invalid_argument("Window already open");
    this->_window = std::make_shared<sf::RenderWindow>();//TODO
}

void WindowManager::clear()
{
    if (!this->_window)
        throw std::invalid_argument("Window must be open");
    this->_window->clear();

}

void WindowManager::refresh()
{
    if (this->_window)
        this->_window->display();
    else
        throw std::invalid_argument("Window must be open");
}

void WindowManager::close()
{
    if (!this->_window)
        throw std::invalid_argument("Window already close");
    this->_window->close();
    this->_window = nullptr;
}