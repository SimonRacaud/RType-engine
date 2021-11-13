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
	MoveUp(Engine::Entity entity, float speed) : _entityId(entity), _speed(speed) {}
	~MoveUp() = default;

	Engine::Entity _entityId;
	float _speed;
};

struct MoveLeft : public Engine::Event::AbstractEvent<MoveLeft> {
	MoveLeft(Engine::Entity entity, float speed) : _entityId(entity), _speed(speed) {}
	~MoveLeft() = default;

	Engine::Entity _entityId;
	float _speed;
};

struct MoveRight : public Engine::Event::AbstractEvent<MoveRight> {
	MoveRight(Engine::Entity entity, float speed) : _entityId(entity), _speed(speed) {}
	~MoveRight() = default;

	Engine::Entity _entityId;
	float _speed;
};

struct MoveDown : public Engine::Event::AbstractEvent<MoveDown> {
	MoveDown(Engine::Entity entity, float speed) : _entityId(entity), _speed(speed) {}
	~MoveDown() = default;

	Engine::Entity _entityId;
	float _speed;
};

struct NotMoving : public Engine::Event::AbstractEvent<NotMoving> {
	NotMoving(Engine::Entity entity) : _entityId(entity) {}
	~NotMoving() = default;

	Engine::Entity _entityId;
};

#endif /* !MOVEEVENTS_HPP_ */
