/*
** EPITECH PROJECT, 2021
** RenderEventDraw
** File description:
** RenderEventDraw.hpp
*/

#ifndef RENDEREVENTDRAW_HPP
#define RENDEREVENTDRAW_HPP

#include "build.hpp"
#include "IEvent.hpp"

class RenderEventDraw : public Engine::Event::IEvent
{
	public:
		RenderEventDraw(renderToolSfml &render) : _render(render)
        {
        }
		~RenderEventDraw() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
		renderToolSfml &_render;
};

#endif