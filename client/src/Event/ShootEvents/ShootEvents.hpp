/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEvents
*/

#ifndef SHOOTEVENTS_HPP_
#define SHOOTEVENTS_HPP_

#include "GameCore/GameCore.hpp"
#include "Event/AbstractEvent/AbstractEvent.hpp"

struct ShootOnce : public Engine::Event::AbstractEvent<ShootOnce> {
	ShootOnce(Engine::Entity e) : _entity(e) {}
	virtual ~ShootOnce() = default;

	Engine::Entity _entity;
};

#endif /* !SHOOTEVENTS_HPP_ */
