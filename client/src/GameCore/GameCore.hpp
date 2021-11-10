/*
** EPITECH PROJECT, 2021
** GameCore
** File description:
** GameCore.hpp
*/

#ifndef GAMECORE_HPP
#define GAMECORE_HPP

#include "build.hpp"
#include "EngineCore.hpp"
#include "EventManager/EventManager.hpp"
#include "WindowManager/WindowManager.hpp"
#include "Event/AudioEvent/AudioEventManager/AudioEventManager.hpp"

class GameCore
{
    public:
        GameCore();
        GameCore(const GameCore &) = delete;
        ~GameCore();

        void run();

    public:
        Engine::IGameEngine &engine;
        Engine::Event::EventCallbackRegister *reg;
        std::shared_ptr<IWindowManager> window;
        std::unique_ptr<IEventManager<renderToolSfml>> event;

    private:
        AudioEventManager _audio;
};

#endif