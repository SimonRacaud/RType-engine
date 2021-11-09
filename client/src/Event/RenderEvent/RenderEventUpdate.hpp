/*
** EPITECH PROJECT, 2021
** RenderEventUpdate
** File description:
** RenderEventUpdate.hpp
*/

#ifndef RENDEREVENTUPDATE_HPP
#define RENDEREVENTUPDATE_HPP

#include "IEvent.hpp"
#include "Interface/IDrawable.hpp"

template<typename uniqueId>
class RenderEventUpdate : public Engine::Event::IEvent
{
	public:
		RenderEventUpdate(uniqueId id, IDrawable *obj) : _id(id), _obj(obj)
        {
        }
		~RenderEventUpdate() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        uniqueId _id;
        IDrawable *_obj;
};

#endif