/*
** EPITECH PROJECT , 2021
** RenderSystem
** File description:
** RenderSystem.cpp
*/

#include <iostream>
#include "RenderSystem.hpp"
#include "Component/Render.hpp"

extern std::shared_ptr<IWindowManager> window;

System::RenderSystem::RenderSystem() : Engine::AbstractSystem<RenderSystem>()
{
    this->setRequirements<Engine::Render>();
}

void System::RenderSystem::run(const std::vector<Engine::Entity> &entities)
{
    for (const Engine::Entity &entity : entities) {
        auto [render] = Engine::EngineFactory::getInstance().getComponentManager().getList<Engine::Render>(entity);

        render._src->draw(window);
    }
}