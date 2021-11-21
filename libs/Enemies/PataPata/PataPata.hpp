/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#ifndef PATAPATA_HPP_
#define PATAPATA_HPP_

#include "IEnemyApi.hpp"

class PataPata : public IEnemyApi {
  public:
    PataPata();
    virtual ~PataPata() = default;

    void idle(const IEnemyApi *ptr) override;
    void move(const IEnemyApi *ptr) override;
    void attack(const IEnemyApi *ptr) override;
    [[nodiscard]] Engine::Position &getPosition() override;
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

#endif /* !PATAPATA_HPP_ */