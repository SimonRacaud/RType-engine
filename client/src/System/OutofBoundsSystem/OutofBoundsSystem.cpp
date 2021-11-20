/*
** EPITECH PROJECT, 2021
** RType
** File description:
** OutofBoundsSystem
*/

#include "OutofBoundsSystem.hpp"

using namespace System;

static const Engine::Time freq = static_cast<Engine::Time>(10);
OutofBoundsSystem::OutofBoundsSystem() : Engine::AbstractSystem<OutofBoundsSystem>(freq, SystemPriority::LOW)
{
	this->setRequirements<Engine::Position, Engine::Velocity, Component::EntityMask>();
}

void OutofBoundsSystem::run(const std::vector<Engine::Entity> &entities)
{
	vector2D windowSize = GameCore::config->getVar<vector2D>("WINDOW_SIZE");
	vector2D playerSize = GameCore::config->getVar<vector2D>("PLAYER_SPRITE_SIZE");
	
	for (const Engine::Entity &e : entities) {
		auto [position, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(e);
		
		if (GET_COMP_M.get<Component::EntityMask>(e)._currentMask != Component::MASK::PLAYER)
			continue;
		if ((position.x + playerSize.x > windowSize.x && velocity.x > 0) || (position.x - playerSize.x < 0 && velocity.x < 0))
			velocity.x = 0;
		if ((position.y + playerSize.y > windowSize.y && velocity.y > 0) || (position.y - playerSize.y < 0 && velocity.y < 0))
			velocity.y = 0;
	}
}