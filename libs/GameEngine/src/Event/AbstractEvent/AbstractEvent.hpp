/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AbstractEvent
*/

#ifndef ABSTRACTEVENT_HPP_
#define ABSTRACTEVENT_HPP_

#include <IEvent.hpp>

namespace Engine {
	namespace Event {
		class AbstractEvent : public IEvent{
			public:
				AbstractEvent();
				~AbstractEvent();
				
				inline std::type_index getType() const override {
					return *_typeIndex;
				}
			private:
				std::type_index *_typeIndex;
		};
	}
}

#endif /* !ABSTRACTEVENT_HPP_ */
