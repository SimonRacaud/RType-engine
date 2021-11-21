/*
** PERSONAL PROJECT, 2021
** WindowManager
** File description:
** WindowManager.cpp
*/

#include "WindowManager.hpp"

std::shared_ptr<sf::RenderWindow> WindowManager::_window = nullptr;

WindowManager::WindowManager(const WindowManager &src): _fps(src._fps), _size(src._size), _name(src._name)
{
}

WindowManager::~WindowManager()
{
    if (this->isOpen())
        WindowManager::_window->close();
    if (WindowManager::_window)
        WindowManager::_window.reset();
}

void WindowManager::setFramerateLimiter(size_t fps)
{
    if (WindowManager::_window)
        WindowManager::_window->setFramerateLimit(fps);
    this->_fps = fps;
}

void WindowManager::setSize(const vector2D &size)
{
    if (WindowManager::_window)
        WindowManager::_window->setSize(sf::Vector2u(size.x, size.y));
    this->_size = size;
}

void WindowManager::setName(const std::string &name)
{
    if (WindowManager::_window)
        WindowManager::_window->setTitle(name);
    this->_name = name;
}

bool WindowManager::isOpen() const
{
    return WindowManager::_window && WindowManager::_window->isOpen();
}

void WindowManager::open()
{
    if (this->isOpen())
        throw std::invalid_argument("Window already open");
    WindowManager::_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->_size.x, this->_size.y),
            this->_name);
    this->setFramerateLimiter(this->_fps);
}

void WindowManager::clear()
{
    if (!WindowManager::_window)
        throw std::invalid_argument("Window must be open");
    WindowManager::_window->clear();

}

void WindowManager::refresh()
{
    if (this->isOpen())
        WindowManager::_window->display();
    else
        throw std::invalid_argument("Window must be open");
}

void WindowManager::close()
{
    if (!WindowManager::_window)
        throw std::invalid_argument("Window already close");
    WindowManager::_window->close();
    WindowManager::_window = nullptr;
}