/*
** EPITECH PROJECT, 2021
** GameCore
** File description:
** GameCore.hpp
*/

#ifndef GAMECORE_HPP
#define GAMECORE_HPP


#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"

#include "build.hpp"
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
        static Engine::IGameEngine &engine;
        static Engine::Event::EventCallbackRegister *reg;
        static std::shared_ptr<IWindowManager> window;
        static std::unique_ptr<IEventManager<renderToolSfml>> event;

    private:
        AudioEventManager _audio;
};

#endif