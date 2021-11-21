/*
** EPITECH PROJECT, 2021
** Bullet
** File description:
** Bullet.cpp
*/

#include "Bullet.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Entities/Explosion/Explosion.hpp"

#include "Component/Render.hpp"
#include "Component/SyncSend.hpp"
#include "Components/EntityMask.hpp"
#include "Components/Hitbox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/EntityMask.hpp"
#include "Component/Damage.hpp"
#include "Event/ExplosionEvents/ExplosionEvents.hpp"
#include "Event/EntityRemove/EntityRemoveEvent.hpp"

Bullet::Bullet(ClusterName cluster, size_t charge, const vector2D &pos, const std::string &type)
{
    std::vector<vector2D> velocity = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_VELOCITY");

    if (velocity.size() != 5)
        throw std::invalid_argument("Velocity must have 5 values");
    if (charge > 4)
        charge = 4;
    *this = Bullet(cluster, charge, pos, velocity[charge], type);
}

Bullet::Bullet(ClusterName cluster, size_t charge, const vector2D &pos, const vector2D &velocity,
    const std::string &type)
{
    std::vector<std::string> sound(GameCore::config->getVectorOf<std::string>("SOUND_BULLET"));

    if (sound.size() != 2)
        throw std::invalid_argument("Need 2 sounds");
    GET_EVENT_REG.registerEvent<AudioEventPlay>(sound[(!charge) ? 0 : 1]);

    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);
    /// GRAPHIC
    std::shared_ptr<AnimationManager> bullet = std::make_shared<AnimationManager>();
    std::vector<vector2D> focusPos = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_ANIMATION_FOCUS_POS");
    std::vector<vector2D> focusSize = GameCore::config->getVectorOf<vector2D>("BULLET_DEFAULT_ANIMATION_FOCUS_SIZE");

    if (focusSize.size() != 5 || focusPos.size() != 5)
        throw std::invalid_argument("focus must have 5 values");
    bullet->setPosition(pos);
    bullet->setFocus(surface(focusPos[charge], focusSize[charge]));
    bullet->setNbMember(GameCore::config->getVar<int>("BULLET_DEFAULT_ANIMATION_STEP"));
    bullet->setSrcPath(GameCore::config->getVar<std::string>("BULLET_DEFAULT_ANIMATION_PATH"));
    componentManager.add<Engine::Render>(entity, bullet);
    ///
    Component::MASK mask;
    if (type == "Player") {
        mask = Component::MASK::BULLET_PLAYER;
        componentManager.add<Component::Damage>(entity, GameCore::config->getVar<int>("BULLET_DAMAGE"));
    } else if (type == "Enemy") {
        mask = Component::MASK::BULLET_ENEMY;
    } else {
        throw std::invalid_argument("Bullet::Bullet invalid owner : " + type);
    }
    componentManager.add<Component::EntityMask>(entity, mask);
    //
    componentManager.add<Engine::Position>(entity, pos.x, pos.y);
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    vector2D size = focusSize[charge];
    /// HITBOX
    componentManager.add<Engine::Hitbox>(entity, size.x, size.y, [](Engine::Entity a, Engine::Entity b) {
        auto mask = GET_COMP_M.get<Component::EntityMask>(a);
        auto otherMask = GET_COMP_M.get<Component::EntityMask>(b);

        if ((mask._currentMask == Component::MASK::BULLET_ENEMY && otherMask._currentMask == Component::MASK::PLAYER) ||
            (mask._currentMask == Component::MASK::BULLET_PLAYER && otherMask._currentMask == Component::MASK::ENEMY)) {
            GET_EVENT_REG.registerEvent<EntityRemoveEvent>(a);
        }
        if (Bullet::displayExplosion(mask._currentMask, otherMask._currentMask))
            GET_EVENT_REG.registerEvent<BulletExplosion>(b);

    });
    /// NETWORK
    if (GameCore::networkCore.isMaster()) {
        componentManager.add<Component::SyncSend>(entity,
            Component::SyncComponentType::POSITION | Component::SyncComponentType::VELOCITY);
    }
    _entity = entity;
}

void Bullet::setNetworkId(uint32_t networkId)
{
    GameCore::engine.getEntityManager().forceApplyId(_entity, networkId);
}

Engine::Entity Bullet::getId() const
{
    return _entity;
}

bool Bullet::displayExplosion(Component::MASK a, Component::MASK b)
{
    using Component::MASK;
    bool bulletA = a == Component::MASK::BULLET_ENEMY || a == Component::MASK::BULLET_PLAYER;
    bool bulletB = b == Component::MASK::BULLET_ENEMY || b == Component::MASK::BULLET_PLAYER;
    bool playerA = a == Component::MASK::PLAYER && b == Component::MASK::BULLET_PLAYER;
    bool playerB = b == Component::MASK::PLAYER && a == Component::MASK::BULLET_PLAYER;
    bool aIsCharacter = a == MASK::PLAYER || a == MASK::ENEMY;
    bool bIsCharacter = b == MASK::PLAYER || b == MASK::ENEMY;

    return !(bulletA && bulletB) && !(playerA || playerB) && (aIsCharacter || bIsCharacter);
}