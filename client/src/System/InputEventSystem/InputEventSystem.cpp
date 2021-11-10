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
extern std::unique_ptr<IEventManager<renderToolSfml>> event;

System::InputEventSystem::InputEventSystem() : Engine::AbstractSystem<InputEventSystem>()
{
    this->setRequirements<Engine::InputEvent>();
}

void System::InputEventSystem::run(const std::vector<Engine::Entity> &entities)
{
    if (event && window->isOpen()) {
        for (const Engine::Entity &entity : entities) {
            auto [eventModule] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::InputEvent>(entity);

            eventModule._func(entity);
        }
        event->refresh(window);
    } else {
        throw std::invalid_argument("Invalid event -> nullptr");
    }
}