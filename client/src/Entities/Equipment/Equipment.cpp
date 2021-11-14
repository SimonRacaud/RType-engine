/*
** EPITECH PROJECT , 2021
** Equipment
** File description:
** \file Equipment.cpp
** \author simon
** \brief
** \date 14/11/2021
*/

#include "Equipment.hpp"

#include "Component/Render.hpp"

#include "AnimationManager/AnimationManager.hpp"

static void hit(Engine::Entity self, Engine::Entity other)
{
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();

    if (componentManager.hasComponent<Engine::ScoreComponent>(other)) {
        // other is a player
        auto &equip = componentManager.get<Engine::EquipmentComponent>(other);
        equip.counter++;
        GameCore::engine.getEntityManager().remove(self);
    }
}

Equipment::Equipment(ClusterName cluster, const vector2D &position)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);
    std::shared_ptr<AnimationManager> anim = std::make_shared<AnimationManager>();
    const vector2D size(32, 32);

    anim->setFocus(surface(vector2D(170, 344), size)); // src pos / size
    anim->setNbMember(4);
    anim->setPosition(position);
    anim->setSrcPath(GameCore::config->getVar<std::string>("SPRITESHEET2"));
    anim->setScale(vector2f(1, 1));

    componentManager.add<Engine::Position>(entity, position.x, position.y);
    componentManager.add<Engine::Velocity>(entity, -1, 0);
    componentManager.add<Engine::Render>(entity, anim);
    componentManager.add<Engine::Hitbox>(entity, size.x, size.y, hit);
}