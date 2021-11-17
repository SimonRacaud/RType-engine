/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ColliderSystem
*/

#include "ColliderSystem.hpp"

using namespace Engine;

static const Engine::Time freq = static_cast<Engine::Time>(50);

ColliderSystem::ColliderSystem() : Engine::AbstractSystem<ColliderSystem>(freq)
{
	this->setRequirements<Engine::Position, Engine::Hitbox>();
}

void ColliderSystem::run(const vector<Entity> &entities)
{
	for (Entity e : entities) {
		for (Entity other : entities) {
			if (other == e || GET_ENTITY_M.getCluster(e) != GET_ENTITY_M.getCluster(other))
				continue;
			auto [position1, hitbox1, mask1] = GET_COMP_M.getList<Engine::Position, Engine::Hitbox, Component::EntityMask>(e);
			auto [position2, hitbox2, mask2] = GET_COMP_M.getList<Engine::Position, Engine::Hitbox, Component::EntityMask>(other);

			if (mask1._currentMask != mask2._currentMask &&
				position1.x < position2.x + hitbox2.x &&
				position1.x + hitbox1.x > position2.x &&
				position1.y < position2.y + hitbox2.y &&
				position1.y + hitbox1.y > position2.y) {
				hitbox1._eventFactory(e, other);
				hitbox2._eventFactory(e, other);
			}
		}	
	}
}
