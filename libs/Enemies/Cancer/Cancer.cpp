/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Cancer
*/

#include "exported.h"
#include "Cancer.hpp"

extern "C" {
    EXPORTED Cancer *initApi();
    Cancer *initApi() {
        return new Cancer();
    }

    EXPORTED void closeApi(Cancer *ptr);
    void closeApi(Cancer *ptr) {
        if (ptr)
            delete ptr;
    }
}

Cancer::Cancer()
	: _position(0, 0), _velocity(-30, 0), _health(5)
{
}

void Cancer::idle(const IEnemyApi *ptr)
{
	(void)ptr;
}

void Cancer::move(const IEnemyApi *ptr)
{
	(void)ptr;
}

void Cancer::attack(const IEnemyApi *ptr)
{
	(void)ptr;
}

Engine::Position &Cancer::getPosition()
{
	return _position;
}

void Cancer::setPosition(vector2D const &position)
{
	_position.x = position.x;
	_position.y = position.y;
}

Engine::Velocity &Cancer::getVelocity()
{
	return _velocity;
}

float Cancer::getShootingSpeed() const
{
	return 1;
}

Component::Health &Cancer::getHealth()
{
	return _health;
}

Component::AnimationInfo Cancer::getAnimInfo() const
{
	return Component::AnimationInfo("asset/sprites/r-typesheet11.gif", 3, {0, 0}, {34, 34});
}

std::pair<float, float> Cancer::getHitboxSize() const
{
	return std::make_pair<float, float>(34, 34);
}