/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EventCallBack
*/

#ifndef EVENTCALLBACK_HPP_
#define EVENTCALLBACK_HPP_

#include <IEventCallback.hpp>
#include <functional>

namespace Engine {
	namespace Event {
		template<class EventType>
		class EventCallBack : public IEventCallback {
			public:
				EventCallBack(std::function<void(const EventType *e)> callback) : _callback(callback) {}
				~EventCallBack() = default;

				inline void call(const IEvent *event) override {
					_callback(reinterpret_cast<const EventType *>(event));
				}

			protected:
				std::function<void(const EventType *)> _callback;
			private:

		};
	}
}

#endif /* !EVENTCALLBACK_HPP_ */
