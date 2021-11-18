/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityHitEvents
*/

#ifndef ENTITYHITEVENTS_HPP_
#define ENTITYHITEVENTS_HPP_

#include "Event/AbstractEvent/AbstractEvent.hpp"
#include "GameCore/GameCore.hpp"

struct EntityHit : public Engine::Event::AbstractEvent<EntityHit> {
	EntityHit(Engine::Entity e, int damage) : _entity(e), _damage(damage) {}
	virtual ~EntityHit() = default;

	Engine::Entity _entity;
	int _damage;
};

#endif /* !ENTITYHITEVENTS_HPP_ */
