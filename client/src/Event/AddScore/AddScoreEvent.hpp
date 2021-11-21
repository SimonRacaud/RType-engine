/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AddScoreEvent
*/

#ifndef ADDSCOREEVENT_HPP_
#define ADDSCOREEVENT_HPP_

#include "Event/AbstractEvent/AbstractEvent.hpp"
#include "EngineCore.hpp"

struct AddScoreEvent : public Engine::Event::AbstractEvent<AddScoreEvent> {
	public:
		AddScoreEvent(const Engine::Entity e) : _entity(e) {}
		virtual ~AddScoreEvent() = default;

		Engine::Entity _entity;
};

#endif /* !ADDSCOREEVENT_HPP_ */
