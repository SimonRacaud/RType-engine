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
#include "AnimationManager/AnimationManager.hpp"
#include "AudioManager/MusicManager/MusicManager.hpp"
#include "AudioManager/SoundManager/SoundManager.hpp"
#include <memory>

void func()
{
    std::shared_ptr<IWindowManager> window = std::make_shared<WindowManager>();
    TextManager text;
    EventManager event;
    SpriteManager sprite;
    AnimationManager animation;
    MusicManager music;
    SoundManager sound;

    window->setName("yolo");
    window->setFramerateLimiter(30);
    window->setSize(vector2D(800, 800));
    window->open();

    text.setColor(ITextManager<renderToolSfml>::color_e::RED);
    text.setContent("mdr");
    text.setFont("asset/font/Code-Bold.ttf");

    sprite.setPosition({100, 100});
    sprite.setSrcFilepath("asset/sprites/r-typesheet1.gif");

    animation.setPosition({10, 10});
    animation.setSrcPath("asset/sprites/r-typesheet1.gif");
    animation.setFocus(surface(vector2D(267, 17), vector2D(33, 34)));
    animation.setNbMember(4);

    music.setAudio("asset/music/R-Type-01_theme.ogg");
    music.play();

    sound.setAudio("asset/sound/shoot.ogg");

    while (window->isOpen()) {
        window->clear();

        // EVENT
        if (event.isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_LEFT))
            sound.play();

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
        animation.draw(window);
        text.draw(window);
        sprite.draw(window);
        // END
        window->refresh();
        event.refresh(window);
    }
    music.pause();
}