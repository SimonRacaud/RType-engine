/*
** EPITECH PROJECT, 2021
** Bullet
** File description:
** Bullet.cpp
*/

#include "Bullet.hpp"
#include "GameCore/GameCore.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Entities/Explosion/Explosion.hpp"

#include "Component/Render.hpp"
#include "Components/Hitbox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

Bullet::Bullet(ClusterName cluster, size_t charge, const vector2D &pos)
{
    std::vector<vector2D> velocity = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_VELOCITY");

    if (velocity.size() != 5)
        throw std::invalid_argument("Velocity must have 5 values");
    if (charge > 4)
        charge = 4;
    *this = Bullet(cluster, charge, pos, velocity[charge]);
}

Bullet::Bullet(ClusterName cluster, size_t charge, const vector2D &pos, const vector2D &velocity)
{
    std::vector<std::string> sound(GameCore::config->getVectorOf<std::string>("SOUND_BULLET"));

    if (sound.size() != 2)
        throw std::invalid_argument("Need 2 sounds");
    GET_EVENT_REG.registerEvent<AudioEventPlay>(sound[(!charge) ? 0 : 1]);

    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);
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
    vector2D size = focusSize[charge];
    componentManager.add<Engine::Hitbox>(entity, size.x, size.y, [cluster](Engine::Entity, Engine::Entity b) {
        static auto last = std::chrono::system_clock::from_time_t(0);
        auto &pos = GET_COMP_M.get<Engine::Position>(b);

        std::chrono::duration<double> tmp = std::chrono::system_clock::now() - last;
        size_t nb_sec = tmp.count();
        std::cout << "EXPLOSION -----------------------> " << nb_sec << " && " << std::chrono::duration<double>(1).count() << std::endl;
        if (nb_sec > std::chrono::duration<double>(1).count()) {
            Explosion(cluster, vector2D(pos.x, pos.y));
            last = std::chrono::system_clock::now();
        }
    });
    componentManager.add<Engine::Render>(entity, bullet);
}