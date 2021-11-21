/*
** EPITECH PROJECT, 2021
** RType
** File description:
** IEnemyApi
*/

#ifndef IENEMYAPI_HPP_
#define IENEMYAPI_HPP_

#include "Components/AnimationInfo.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

class IEnemyApi {
  public:
    ~IEnemyApi() = default;

    virtual void idle(const IEnemyApi *ptr) = 0;
    virtual void move(const IEnemyApi *ptr) = 0;
    virtual void attack(const IEnemyApi *ptr) = 0;
    virtual void setPosition(vector2D const &position) = 0;
    virtual Engine::Position &getPosition() = 0;
    virtual Engine::Velocity &getVelocity() = 0;
    [[nodiscard]] virtual float getShootingSpeed() const = 0;
    virtual Component::Health &getHealth() = 0;
    [[nodiscard]] virtual Component::AnimationInfo getAnimInfo() const = 0;
    [[nodiscard]] virtual std::pair<float, float> getHitboxSize() const = 0;
};

#endif /* !IEnemyApi_HPP_ */