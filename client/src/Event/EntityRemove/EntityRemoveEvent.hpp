/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveEvent
*/

#ifndef ENTITYREMOVEEVENT_HPP_
#define ENTITYREMOVEEVENT_HPP_

#include "EngineCore.hpp"
#include "Event/AbstractEvent/AbstractEvent.hpp"

struct EntityRemoveEvent : public Engine::Event::AbstractEvent<EntityRemoveEvent> {
		EntityRemoveEvent(Engine::Entity e) : _entity(e) {}
		virtual ~EntityRemoveEvent() = default;

		Engine::Entity _entity;
};

#endif /* !ENTITYREMOVEEVENT_HPP_ */
