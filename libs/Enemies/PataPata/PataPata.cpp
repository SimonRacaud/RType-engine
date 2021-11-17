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
}

PataPata::PataPata()
	: _position(0, 0), _velocity(10, 10), _health(1)
{
}

PataPata::~PataPata()
{
}

void PataPata::idle(const IEnemyApi *ptr) 
{
	std::cout << "PataPata idle\n";
}

void PataPata::move(const IEnemyApi *ptr) 
{
	std::cout << "PataPata move\n";
}

void PataPata::attack(const IEnemyApi *ptr) 
{
	std::cout << "PataPata attack\n";
}

float PataPata::getShootingSpeed() const 
{
	return 1;
}

Engine::Position &PataPata::getPosition()
{
	return _position;
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
	return Component::AnimationInfo("asset/sprites/r-typesheet5.gif", 8, {4, 5}, {25, 27});
}

std::pair<float, float> PataPata::getHitboxSize() const
{
	return std::make_pair<float, float>(25, 27);
}