/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#include "PataPata.hpp"
#include "exported.h"

extern "C" {
	EXPORTED PataPata *initApi();
	PataPata *initApi() {
		return new PataPata();
	}

	EXPORTED void closeApi(PataPata *ptr);
	void closeApi(PataPata *ptr) {
		if (ptr)
			delete ptr;
	}
}

PataPata::PataPata()
	: _position(0, 0), _velocity(-50, 0), _health(1)
{
}

void PataPata::idle(const IEnemyApi *ptr)
{
	(void)ptr;
}

void PataPata::move(const IEnemyApi *ptr)
{
	(void)ptr;
}

void PataPata::attack(const IEnemyApi *ptr)
{
	(void)ptr;
}

float PataPata::getShootingSpeed() const
{
	return 1;
}

Engine::Position &PataPata::getPosition()
{
	return _position;
}

void PataPata::setPosition(const vector2D &position)
{
    this->_position.x = position.x;
    this->_position.y = position.y;
}

Engine::Velocity &PataPata::getVelocity()
{
	return _velocity;
}

Component::Health &PataPata::getHealth()
{
	return _health;
}

Component::AnimationInfo PataPata::getAnimInfo() const
{
	return Component::AnimationInfo("asset/sprites/r-typesheet5.gif", 8, {0, 0}, {33, 36});
}

std::pair<float, float> PataPata::getHitboxSize() const
{
	return std::make_pair<float, float>(25, 27);
}