/*
** EPITECH PROJECT, 2021
** Explosion
** File description:
** Explosion.cpp
*/

#include "Explosion.hpp"
#include "Component/Render.hpp"
#include "GameCore/GameCore.hpp"
#include "AnimationManager/AnimationManager.hpp"

Explosion::Explosion(ClusterName cluster, const vector2D &pos)
{
    std::string sound = GameCore::config->getVar<std::string>("SOUND_EXPLOSION");

    GET_EVENT_REG.registerEvent<AudioEventPlay>(sound);
    
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);
    std::shared_ptr<AnimationManager> anim = std::make_shared<AnimationManager>();

    vector2D sizeAnim = GameCore::config->getVar<vector2D>("EXPLOSION_ANIMATION_FOCUS_SIZE");

    anim->setPosition(pos);
    anim->setFocus(surface(GameCore::config->getVar<vector2D>("EXPLOSION_ANIMATION_FOCUS_POS"), sizeAnim));
    anim->setNbMember(GameCore::config->getVar<int>("EXPLOSION_ANIMATION_STEP"));
    anim->setSrcPath(GameCore::config->getVar<std::string>("EXPLOSION_ANIMATION_PATH"));

    int animDuration = GameCore::config->getVar<int>("EXPLOSION_ANIMATION_DURATION");

    componentManager.add<Engine::Render>(entity, anim);
    componentManager.add<Engine::Position>(entity, pos.x - sizeAnim.x / 2, pos.y - sizeAnim.y / 2);
    componentManager.add<Engine::Timer>(entity, std::chrono::milliseconds(animDuration), [](Engine::Entity a) {
        std::cout << "DESTROY -> EXPLOSION" << std::endl;
        GameCore::engine.getEntityManager().remove(a);
    });
    _entity = entity;
}

void Explosion::setNetworkId(uint32_t)
{
    GameCore::engine.getEntityManager().setNetworkId(_entity);
}