/*
** EPITECH PROJECT, 2021
** GameCore
** File description:
** GameCore.cpp
*/

#include "GameCore.hpp"

GameCore::GameCore() :
engine(Engine::EngineFactory::getInstance()),
reg(new Engine::Event::EventCallbackRegister()),
window(std::make_shared<WindowManager>()),
event(std::make_unique<EventManager>())
{
    window->setName("yolo");
    window->setFramerateLimiter(30);
    window->setSize(vector2D(800, 800));
    window->open();
}

GameCore::~GameCore()
{
}

void GameCore::run()
{
}