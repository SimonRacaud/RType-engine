/*
** PERSONAL PROJECT, 2021
** SfmlModule
** File description:
** SfmlModule.cpp
*/

/*#include <iostream>
#include <SFML/Graphics.hpp>

void func()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}*/

#include "TextManager/TextManager.hpp"
#include "EventManager/EventManager.hpp"
#include "WindowManager/WindowManager.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include <memory>

void func()
{
    std::shared_ptr<IWindowManager> window = std::make_shared<WindowManager>();
    TextManager text;
    EventManager event;
    SpriteManager sprite;

    window->setName("yolo");
    window->setFramerateLimiter(30);
    window->setSize(vector2D(800, 800));
    window->open();

    text.setColor(ITextManager<renderToolSfml>::color_e::RED);
    text.setContent("mdr");
    text.setFont("asset/font/Code-Bold.ttf");

    sprite.setPosition({0, 0});
    sprite.setSrcFilepath("asset/sprites/r-typesheet1.gif");

    while (window->isOpen()) {
        window->clear();
        // DRAW
        text.draw(window);
        sprite.draw(window);
        // END
        window->refresh();
        event.refresh(window);
    }
}