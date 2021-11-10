/*
** EPITECH PROJECT , 2021
** RenderSystem
** File description:
** RenderSystem.cpp
*/

#include <iostream>
#include "RenderSystem.hpp"
#include "Component/Render.hpp"
#include "GameCore/GameCore.hpp"

System::RenderSystem::RenderSystem() : Engine::AbstractSystem<RenderSystem>()
{
    this->setRequirements<Engine::Render>();
}

void System::RenderSystem::run(const std::vector<Engine::Entity> &entities)
{
    if (GameCore::window && GameCore::window->isOpen()) {
        GameCore::window->clear();
        for (const Engine::Entity &entity : entities) {
            auto [render] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::Render>(entity);

            render._src->draw(GameCore::window);
        }
        GameCore::window->refresh();
    } else {
        throw std::invalid_argument("Window is close");
    }
}