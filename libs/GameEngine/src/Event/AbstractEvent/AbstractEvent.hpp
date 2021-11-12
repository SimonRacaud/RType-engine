/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AbstractEvent
*/

#ifndef ABSTRACTEVENT_HPP_
#define ABSTRACTEVENT_HPP_

#include "Event/IEvent.hpp"
#include "global.hpp"

namespace Engine {
	namespace Event {
		template<typename EventType>
		class AbstractEvent : public IEvent {
			public:
				AbstractEvent() = default;
				~AbstractEvent() = default;
				
				virtual std::type_index getType() const override {
					return type;
				}
				static const TypeIdx type;
		};
	}
}
template<typename EventType>
const Engine::TypeIdx Engine::Event::AbstractEvent<EventType>::type = GET_TYPE_IDX(Engine::Event::AbstractEvent<EventType>);

#endif /* !ABSTRACTEVENT_HPP_ */
