/*
** PERSONAL PROJECT, 2021
** SfmlModule
** File description:
** SfmlModule.cpp
*/

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

        // EVENT
        if (event.isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_UP))
            text.setColor(ITextManager<renderToolSfml>::color_e::BLUE);
        else if (event.mouseIsOnClick(surface(vector2D(0, 0), vector2D(200, 200)), IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_MIDDLE))
            text.setColor(ITextManager<renderToolSfml>::color_e::GREEN);
        else if (event.mouseIsOn(surface(vector2D(0, 0), vector2D(200, 200))))
            text.setColor(ITextManager<renderToolSfml>::color_e::WHITE);
        else
            text.setColor(ITextManager<renderToolSfml>::color_e::RED);

        text.setPosition(event.getMousePos());
        text.refresh();
        // END
        
        // DRAW
        text.draw(window);
        sprite.draw(window);
        // END
        window->refresh();
        event.refresh(window);
    }
}