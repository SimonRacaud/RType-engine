/*
** EPITECH PROJECT, 2021
** RenderEventManager
** File description:
** RenderEventManager.hpp
*/

#ifndef RENDEREVENTMANAGER_HPP
#define RENDEREVENTMANAGER_HPP

#include <unordered_map>
#include "IEvent.hpp"
#include "Event/RenderEvent/RenderEventAdd.hpp"
#include "Event/RenderEvent/RenderEventDraw.hpp"
#include "Event/RenderEvent/RenderEventRemove.hpp"
#include "Event/RenderEvent/RenderEventUpdate.hpp"

class RenderEventManager
{
    using uniqueId = std::string;
	public:
		RenderEventManager();
		~RenderEventManager();

	private:
        static void add(const RenderEventAdd *e);
        static void draw(const RenderEventDraw *e);
        static void Remove(const RenderEventRemove *e);
        static void Update(const RenderEventUpdate *e);

    private:
        std::unordered_map<uniqueId, IDrawable *> _list;
};

#endif