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

struct PlayerEquipmentHit : public Engine::Event::AbstractEvent<PlayerEquipmentHit> {
	PlayerEquipmentHit(Engine::Entity e, Engine::Entity equipment) : _entity(e), _equipment(equipment) {}
	virtual ~PlayerEquipmentHit() = default;

	Engine::Entity _entity;
	Engine::Entity _equipment;
};

#endif /* !ENTITYHITEVENTS_HPP_ */
