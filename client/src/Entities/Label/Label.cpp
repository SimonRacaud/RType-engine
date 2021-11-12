/*
** EPITECH PROJECT , 2021
** Label
** File description:
** \file Label.cpp
** \author simon
** \brief
** \date 12/11/2021
*/

#include "Label.hpp"

#include "GameCore/GameCore.hpp"
#include "Component/Render.hpp"
#include "TextManager/TextManager.hpp"

Label::Label(Engine::ClusterName cluster, const string &content,
    const vector2D &position, vector2D const &size, color_e color)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);
    string font = GameCore::config->getVar<string>("FONT");

    componentManager.add<Engine::Render>(entity,
        std::make_unique<TextManager>(position, size, color, content, font));
    componentManager.add<Engine::Position>(entity, (float)position.x, (float)position.y);
}

Label::Label(Engine::ClusterName cluster, size_t content,
    const vector2D &position, vector2D const &size, color_e color)
{
    Label(cluster, std::to_string(content), position, size, color);
}