/*
** EPITECH PROJECT, 2021
** RType
** File description:
** IEventCallback
*/

#ifndef IEVENTCALLBACK_HPP_
#define IEVENTCALLBACK_HPP_

#include "IEvent.hpp"

namespace Engine {
	namespace Event {
		class IEventCallback {
			public:
				virtual ~IEventCallback() = default;
				virtual void call(const IEvent *event) = 0;
		};
	}
}

#endif /* !IEVENTCALLBACK_HPP_ */
