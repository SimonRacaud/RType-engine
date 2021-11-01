/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EventCallBackRegister
*/

#ifndef EVENTCALLBACKREGISTER_HPP_
#define EVENTCALLBACKREGISTER_HPP_

#include <unordered_map>
#include <iostream>
#include <queue>
#include "EventCallBack.hpp"
#include <memory>
#include <functional>

namespace Engine {
	namespace Event {
		class EventCallBackRegister {
			public:
				EventCallBackRegister() = default;
				~EventCallBackRegister() = default;

				void execQueue()
				{
					IEvent *e;

					while (_queue.size() > 0) {
						e = _queue.front();
						if (_registeredCallbacks.find(std::type_index(typeid(*e))) != _registeredCallbacks.end()) {
							_registeredCallbacks[std::type_index(typeid(*e))]->call(e);
						} else
							std::cout << "Event with no registered callbacks, skipping" << std::endl;
						_queue.pop();
					}
				}

				template<class EventType>
				void registerCallback(std::function<void(const EventType*)> callback) {
					IEventCallback *func = new EventCallBack<EventType>(callback);
					
					_registeredCallbacks[std::type_index(typeid(EventType))] = func;
				}

				template<class EventType, class... Args>
				void dispatch(Args&&... eventArgs) {
					EventType *e = new EventType(std::forward<Args>(eventArgs)...);
					
					_queue.push(e);
				}

			private:
				template<class EventType>
				void checkType() {
					std::cout << std::type_index(typeid(EventType)).hash_code() << std::endl;
				}
				std::unordered_map<std::type_index, IEventCallback *> _registeredCallbacks;
				std::queue<IEvent *> _queue;
		};

	}
}

#endif /* !EVENTCALLBACKREGISTER_HPP_ */
