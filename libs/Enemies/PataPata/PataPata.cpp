/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#include "PataPata.hpp"

PataPata::PataPata()
	: _position(0, 0), _velocity(10, 10), _health(1)
{
}

PataPata::~PataPata()
{
}

void PataPata::idle(const PataPata *ptr) 
{
	std::cout << "PataPata idle\n";
}

void PataPata::move(const PataPata *ptr) 
{
	std::cout << "PataPata move\n";
}

void PataPata::attack(const PataPata *ptr) 
{
	std::cout << "PataPata attack\n";
}

float PataPata::getShootingSpeed() const 
{
	return 1;
}

Component::Position &PataPata::getPosition()
{
	return _position;
}

Component::Velocity &PataPata::getVelocity()
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