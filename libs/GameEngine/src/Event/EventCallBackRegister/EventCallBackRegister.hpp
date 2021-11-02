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
				~EventCallBackRegister() {

				}

				void execQueue()
				{
					std::shared_ptr<IEvent> e;

					while (_queue.size() > 0) {
						e = _queue.front();
						if (_registeredCallbacks.find(std::type_index(typeid(*e))) != _registeredCallbacks.end()) {
							_registeredCallbacks[std::type_index(typeid(*e))]->call(e.get());
						} else {
							std::cout << "Event with no registered callbacks, skipping" << std::endl;
						}
						_queue.pop();
					}
				}

				template<class EventType>
				void registerCallback(std::function<void(const EventType*)> callback) {
					std::shared_ptr<IEventCallback> func = std::make_shared<EventCallBack<EventType>>(callback);
					
					_registeredCallbacks[std::type_index(typeid(EventType))] = func;
				}

				template<class EventType, class... Args>
				void registerEvent(Args&&... eventArgs) {
					std::shared_ptr<EventType> e = std::make_shared<EventType>(std::forward<Args>(eventArgs)...);
					
					_queue.push(e);
				}

			private:
				template<class EventType>
				void checkType() {
					std::cout << std::type_index(typeid(EventType)).hash_code() << std::endl;
				}
				std::unordered_map<std::type_index, std::shared_ptr<IEventCallback>> _registeredCallbacks;
				std::queue<std::shared_ptr<IEvent>> _queue;
		};

	}
}

#endif /* !EVENTCALLBACKREGISTER_HPP_ */
