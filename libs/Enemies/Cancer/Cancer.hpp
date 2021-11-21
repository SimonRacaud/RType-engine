/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Cancer
*/

#ifndef CANCER_HPP_
#define CANCER_HPP_

#include "IEnemyApi.hpp"

class Cancer : public IEnemyApi {
  public:
    Cancer();
    virtual ~Cancer() = default;

    void idle(const IEnemyApi *ptr) override;
    void move(const IEnemyApi *ptr) override;
    void attack(const IEnemyApi *ptr) override;
    Engine::Position &getPosition() override;
    void setPosition(vector2D const &position) override;
    Engine::Velocity &getVelocity() override;
    [[nodiscard]] float getShootingSpeed() const override;
    Component::Health &getHealth() override;
    [[nodiscard]] Component::AnimationInfo getAnimInfo() const override;
    [[nodiscard]] std::pair<float, float> getHitboxSize() const override;

  private:
    Engine::Position _position;
    Engine::Velocity _velocity;
    Component::Health _health;
};

#endif /* !CANCER_HPP_ */