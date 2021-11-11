/*
** EPITECH PROJECT , 2021
** InputEventSystem
** File description:
** InputEventSystem.cpp
*/

#include <iostream>
#include "InputEventSystem.hpp"
#include "GameCore/GameCore.hpp"
#include "Component/InputEvent.hpp"

System::InputEventSystem::InputEventSystem() : Engine::AbstractSystem<InputEventSystem>()
{
    this->setRequirements<Engine::InputEvent>();
}

void System::InputEventSystem::run(const std::vector<Engine::Entity> &entities)
{
    if (GameCore::event && GameCore::window->isOpen()) {
        for (const Engine::Entity &entity : entities) {
            auto [eventModule] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::InputEvent>(entity);

            eventModule._func(entity);
        }
        GameCore::event->refresh(GameCore::window);
    } else {
        throw std::invalid_argument("Invalid event -> nullptr");
    }
    if (!GameCore::window->isOpen())
        GameCore::engine.quit();
}