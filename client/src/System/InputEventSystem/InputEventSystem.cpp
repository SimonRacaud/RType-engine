/*
** EPITECH PROJECT , 2021
** InputEventSystem
** File description:
** InputEventSystem.cpp
*/

#include <iostream>
#include "InputEventSystem.hpp"
#include "Component/InputEvent.hpp"

extern std::shared_ptr<IWindowManager> window;

System::InputEventSystem::InputEventSystem() : Engine::AbstractSystem<InputEventSystem>()
{
    this->setRequirements<Engine::InputEvent>();
}

void System::InputEventSystem::run(const std::vector<Engine::Entity> &entities)
{
    for (const Engine::Entity &entity : entities) {
        auto [event] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::InputEvent>(entity);

        event._func(entity);
    }
}