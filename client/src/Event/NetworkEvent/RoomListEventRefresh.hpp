/*
** EPITECH PROJECT, 2021
** RoomListEventRefresh
** File description:
** RoomListEventRefresh.hpp
*/

#ifndef ROOMLISTEVENTREFRESH_HPP
#define ROOMLISTEVENTREFRESH_HPP

#include "Event/IEvent.hpp"

class RoomListEventRefresh : public Engine::Event::IEvent
{
	public:
		RoomListEventRefresh()
        {
        }
		~RoomListEventRefresh() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
};

#endif