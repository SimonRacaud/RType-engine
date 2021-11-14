/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#include "PataPata.hpp"

PataPata::PataPata()
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

float PataPata::getMoveSpeed() const 
{
	return 10;
}

float PataPata::getShootingSpeed() const 
{
	return 1;
}

int PataPata::getHealth() const 
{
	return 1;
}

std::string PataPata::getSpriteSheet() const 
{
	return std::string("asset/sprites/r-typesheet5.gif");
}

int PataPata::getAnimationNbFrames() const 
{
	return 0;
}

vector2D PataPata::getIdleAnimPos() const 
{
	return vector2D(2, 3);
}

vector2D PataPata::getMoveAnimPos() const 
{
	return vector2D(2, 3);
}

vector2D PataPata::getAttackAnimPos() const 
{
	return vector2D(2, 3);
}

