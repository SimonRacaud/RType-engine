/*
** EPITECH PROJECT, 2021
** Bullet
** File description:
** Bullet.cpp
*/

#include "Bullet.hpp"
#include "GameCore/GameCore.hpp"
#include "AnimationManager/AnimationManager.hpp"

#include "Component/Render.hpp"
#include "Components/Hitbox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

Bullet::Bullet(size_t charge, const vector2D &pos)
{
    vector2D velocity = GameCore::config->getVar<vector2D>("BULLET_DEFAULT_VELOCITY");

    if (charge > 4)
        charge = 4;
    *this = Bullet(charge, pos, velocity);
}

Bullet::Bullet(size_t charge, const vector2D &pos, const vector2D &velocity)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::EMPTY);
    std::shared_ptr<AnimationManager> bullet = std::make_shared<AnimationManager>();
    std::vector<vector2D> focusPos = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_ANIMATION_FOCUS_POS");
    std::vector<vector2D> focusSize = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_ANIMATION_FOCUS_SIZE");

    if (focusSize.size() != 5 || focusPos.size() != 5)
        throw std::invalid_argument("focus must have 5 values");
    bullet->setPosition(pos);
    bullet->setFocus(surface(focusPos[charge], focusSize[charge]));
    bullet->setNbMember(GameCore::config->getVar<int>("BULLET_DEFAULT_ANIMATION_STEP"));
    bullet->setSrcPath(GameCore::config->getVar<std::string>("BULLET_DEFAULT_ANIMATION_PATH"));

    componentManager.add<Engine::Position>(entity, pos.x, pos.y);
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    /*vector2D size = focusSize[charge];
    componentManager.add<Engine::Hitbox>(entity, size.x, size.y, [](Engine::Entity a, Engine::Entity b) {
        GameCore::engine.getEntityManager().remove(a);
        GameCore::engine.getEntityManager().remove(b);
        // ADD EXPLOSION ANIMATION
    });*/
    componentManager.add<Engine::Render>(entity, bullet);
}