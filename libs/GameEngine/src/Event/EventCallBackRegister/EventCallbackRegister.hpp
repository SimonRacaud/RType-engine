/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EventCallbackRegister
*/

#ifndef EVENTCALLBACKREGISTER_HPP_
#define EVENTCALLBACKREGISTER_HPP_

#include <unordered_map>
#include <iostream>
#include <queue>
#include "Event/EventCallBack/EventCallBack.hpp"
#include <memory>
#include <functional>

namespace Engine::Event {
		class EventCallbackRegister {
			public:
				EventCallbackRegister() = default;
				~EventCallbackRegister() {}

				void execQueue()
				{
					std::shared_ptr<IEvent> e;

					while (!_queue.empty()) {
						e = _queue.front();
						std::unordered_map<std::type_index, std::shared_ptr<IEventCallback>>::iterator it = _registeredCallbacks.find(std::type_index(typeid(*e)));
						if (it != _registeredCallbacks.end() && it->second != nullptr) {
                            try {
                                it->second->call(e.get());
                            } catch (std::exception const &excep) {
                                std::cerr << "EventCallbackRegister::execQueue " << excep.what() << std::endl;
                                exit(84); // TODO
                            }
						} else {
							std::cerr << "Event with no registered callbacks, skipping" << std::endl;
						}
						_queue.pop();
					}
				}

				template<class EventType>
				void registerCallback(std::function<void(const EventType *)> callback) {
					std::shared_ptr<IEventCallback> func = std::make_shared<EventCallBack<EventType>>(callback);

					_registeredCallbacks[std::type_index(typeid(EventType))] = func;
				}

				template<class EventType>
				void removeCallback(std::shared_ptr<IEventCallback> &) {
					// implement operator == for callbacks
					// std::shared_ptr<IEventCallback> func = _registeredCallbacks[std::type_index(typeid(EventType))];

					// if (func == _registeredCallbacks.end()) {
					// 	std::cerr << "Trying to remove a callback that does not exist" << std::endl;
					// 	return;
					// }
					// if (*func == *callback) {
					// 	_registeredCallbacks[std::type_index(typeid(EventType))] = nullptr;
					// }
				}

				template<class EventType, class... Args>
				void registerEvent(Args&&... eventArgs) {

					checkType<EventType>();
					std::shared_ptr<Engine::Event::IEvent> e = std::make_shared<EventType>(std::forward<Args>(eventArgs)...);

					_queue.push(e);
				}

				void registerEvent(std::shared_ptr<Engine::Event::IEvent> e) {
					_queue.push(e);
				}

			private:
				template<class EventType>
				void checkType() {
					static_assert(std::is_base_of<IEvent, EventType>::value, "Invalid event type");
				}
				std::unordered_map<std::type_index, std::shared_ptr<IEventCallback>> _registeredCallbacks;
				std::queue<std::shared_ptr<IEvent>> _queue;
		};
	}

#endif /* !EVENTCALLBACKREGISTER_HPP_ */