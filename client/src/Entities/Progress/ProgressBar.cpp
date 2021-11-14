/*
** EPITECH PROJECT , 2021
** ProgressBar
** File description:
** \file ProgressBar.cpp
** \author simon
** \brief
** \date 13/11/2021
*/

#include "ProgressBar.hpp"

#include "GameCore/GameCore.hpp"
#include "Component/Render.hpp"
#include "ShapeManager/ShapeManager.hpp"

ProgressBar::ProgressBar(
    ClusterName cluster,
    EntityName name,
    const vector2D &position,
    const vector2D &size,
    color_e primaryColor,
    color_e backgroundColor)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, name);

    std::vector<size_t> selectedLayer;
    std::vector<Engine::DrawableObj> layers;
    layers.push_back(std::make_unique<ShapeManager>(position, vector2D(0, size.y), primaryColor));
    layers.push_back(std::make_unique<ShapeManager>(position, size, backgroundColor));
    selectedLayer.push_back(0);
    selectedLayer.push_back(1);

    componentManager.add<Engine::Render>(entity, layers, selectedLayer);
    componentManager.add<Engine::NumberComponent>(entity, 0);
    componentManager.add<Component::Position>(entity, (float)position.x, (float)position.y);
}