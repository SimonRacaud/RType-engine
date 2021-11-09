/*
** EPITECH PROJECT, 2021
** RenderEventManager
** File description:
** RenderEventManager.hpp
*/

#ifndef RENDEREVENTMANAGER_HPP
#define RENDEREVENTMANAGER_HPP

#include <unordered_map>
#include "build.hpp"
#include "Event/IEvent.hpp"
#include "Event/RenderEvent/RenderEventAdd.hpp"
#include "Event/RenderEvent/RenderEventDraw.hpp"
#include "Event/RenderEvent/RenderEventRemove.hpp"
#include "Event/RenderEvent/RenderEventUpdate.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

extern Engine::Event::EventCallbackRegister *reg;

class RenderEventManager
{
    using uniqueId = std::string;
	public:
		RenderEventManager();
		~RenderEventManager();

        void add(const RenderEventAdd<uniqueId> *e);
        void draw(const RenderEventDraw *e);
        void remove(const RenderEventRemove<uniqueId> *e);
        void update(const RenderEventUpdate<uniqueId> *e);

    private:
        std::unordered_map<uniqueId, IDrawable<renderToolSfml> *> _list;
};

#endif