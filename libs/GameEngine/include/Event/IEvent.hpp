/*
** EPITECH PROJECT, 2021
** RType
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
#define IEVENT_HPP_

#include <typeindex>

namespace Engine {
	namespace Event {
		class IEvent {
			public:
				virtual ~IEvent() = default;

				virtual std::type_index getType() const = 0;
		};
	}
}

#endif /* !IEVENT_HPP_ */
