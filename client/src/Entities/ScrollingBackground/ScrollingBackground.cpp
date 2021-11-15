/*
** EPITECH PROJECT, 2021
** ScrollingBackground
** File description:
** ScrollingBackground.cpp
*/

#include <memory>

#include "GameCore/GameCore.hpp"
#include "ScrollingBackground.hpp"

#include "Component/Render.hpp"
#include "Component/Scroll.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

#include "SpriteManager/SpriteManager.hpp"

ScrollingBackground::ScrollingBackground(Engine::ClusterName clusterName)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, clusterName, Engine::EntityName::EMPTY);

    vector2D win = GameCore::config->getVar<vector2D>("WINDOW_SIZE");
    vector2D pos = GameCore::config->getVar<vector2D>("SCROLLING_DEFAULT_POS");
    vector2D velocity = GameCore::config->getVar<vector2D>("SCROLLING_DEFAULT_VELOCITY");
    std::string path = GameCore::config->getVar<std::string>("SCROLLING_DEFAULT_PATH");

    componentManager.add<Engine::Render>(entity, std::make_shared<SpriteManager>(pos, vector2f(1, 1), path));
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    componentManager.add<Component::Scroll>(entity, win.x * 2);
    componentManager.add<Engine::Velocity>(entity, pos.x, pos.y);
}