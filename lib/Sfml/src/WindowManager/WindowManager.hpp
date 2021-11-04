/*
** PERSONAL PROJECT, 2021
** WindowManager
** File description:
** WindowManager.hpp
*/

#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "Interface/IWindowManager.hpp"

class WindowManager: public IWindowManager
{
    public:
        WindowManager();
        WindowManager(const WindowManager &);
        ~WindowManager();

        void setFramerateLimiter(size_t);
        void setSize(const vector2D &);
        void setName(const std::string &);
        bool isOpen() const;
        void open();
        void clear();
        void refresh();
        void close();
    
    public:
        std::shared_ptr<sf::RenderWindow> _window;

    private:
        size_t _fps;
        vector2D _size;
        std::string _name;
};

#endif