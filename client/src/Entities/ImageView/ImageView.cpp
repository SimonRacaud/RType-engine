/*
** EPITECH PROJECT , 2021
** ImageView
** File description:
** \file ImageView.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "ImageView.hpp"

#include "GameCore/GameCore.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "Component/Render.hpp"

ImageView::ImageView(const std::string &path, const vector2D &position,
    const vector2f &scale, Engine::ClusterName cluster)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);

    componentManager.add<Engine::Render>(entity,
        std::make_unique<SpriteManager>(position, scale, path));
    componentManager.add<Engine::Velocity>(entity, (float)position.x, (float)position.y);
}