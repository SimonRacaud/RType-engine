/*
** EPITECH PROJECT, 2021
** RenderEventAdd
** File description:
** RenderEventAdd.hpp
*/

#ifndef RENDEREVENTADD_HPP
#define RENDEREVENTADD_HPP

#include "IEvent.hpp"
#include "Interface/IDrawable.hpp"

template<typename uniqueId>
class RenderEventAdd : public Engine::Event::IEvent
{
	public:
		RenderEventAdd(uniqueId id, IDrawable *obj) : _id(id), _obj(obj)
        {
        }
		~RenderEventAdd() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        uniqueId _id;
        IDrawable *_obj;
};

#endif