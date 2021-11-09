/*
** EPITECH PROJECT, 2021
** RenderEventRemove
** File description:
** RenderEventRemove.hpp
*/

#ifndef RENDEREVENTREMOVE_HPP
#define RENDEREVENTREMOVE_HPP

#include "IEvent.hpp"

template<typename uniqueId>
class RenderEventRemove : public Engine::Event::IEvent
{
	public:
		RenderEventRemove(uniqueId id) : _id(id)
        {
        }
		~RenderEventRemove() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        uniqueId _id;
};

#endif