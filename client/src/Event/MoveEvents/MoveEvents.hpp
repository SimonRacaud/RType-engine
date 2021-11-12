/*
** EPITECH PROJECT, 2021
** RType
** File description:
** MoveEvents
*/

#ifndef MOVEEVENTS_HPP_
#define MOVEEVENTS_HPP_

#include "GameCore/GameCore.hpp"
#include "Event/AbstractEvent/AbstractEvent.hpp"

struct MoveUp : public Engine::Event::AbstractEvent<MoveUp> {
	MoveUp(Engine::Entity entity) : _entityId(entity) {}
	~MoveUp() = default;

	Engine::Entity _entityId;
};

struct MoveLeft : public Engine::Event::AbstractEvent<MoveLeft> {
	MoveLeft(Engine::Entity entity) : _entityId(entity) {}
	~MoveLeft() = default;

	Engine::Entity _entityId;
};

struct MoveRight : public Engine::Event::AbstractEvent<MoveRight> {
	MoveRight(Engine::Entity entity) : _entityId(entity) {}
	~MoveRight() = default;

	Engine::Entity _entityId;
};

struct MoveDown : public Engine::Event::AbstractEvent<MoveDown> {
	MoveDown(Engine::Entity entity) : _entityId(entity) {}
	~MoveDown() = default;

	Engine::Entity _entityId;
};

#endif /* !MOVEEVENTS_HPP_ */
