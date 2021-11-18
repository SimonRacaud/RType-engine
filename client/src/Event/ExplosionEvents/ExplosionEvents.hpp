/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ExplosionEvents
*/

#ifndef EXPLOSIONEVENTS_HPP_
#define EXPLOSIONEVENTS_HPP_

#include "Event/AbstractEvent/AbstractEvent.hpp"
#include "EngineCore.hpp"

struct BulletExplosion : public Engine::Event::AbstractEvent<BulletExplosion> {
	BulletExplosion(Engine::Entity e) : _entity(e) {}
	virtual ~BulletExplosion() = default;

	Engine::Entity _entity;
};

#endif /* !EXPLOSIONEVENTS_HPP_ */
