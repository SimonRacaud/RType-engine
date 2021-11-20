/*
** EPITECH PROJECT, 2021
** JoinRoomEvent
** File description:
** JoinRoomEvent.hpp
*/

#ifndef JOINEVENTEVENT_HPP
#define JOINEVENTEVENT_HPP

#include <cstddef>
#include "Event/IEvent.hpp"

class JoinRoomEvent : public Engine::Event::IEvent
{
	public:
		JoinRoomEvent(size_t roomId) : _roomId(roomId)
        {
        }
		~JoinRoomEvent() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

        size_t _roomId;
};

#endif