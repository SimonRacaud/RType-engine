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
        WindowManager() = default;
        WindowManager(const WindowManager &);
        ~WindowManager();

        void setFramerateLimiter(size_t) override;
        void setSize(const vector2D &) override;
        void setName(const std::string &) override;
        [[nodiscard]] bool isOpen() const override;
        void open() override;
        void clear() override;
        void refresh() override;
        void close() override;

    public:
        static std::shared_ptr<sf::RenderWindow> _window;

    private:
        size_t _fps{0};
        vector2D _size{0, 0};
        std::string _name;
};

#endif