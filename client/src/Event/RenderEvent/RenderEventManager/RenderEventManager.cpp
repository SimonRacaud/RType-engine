/*
** EPITECH PROJECT, 2021
** RenderEventManager
** File description:
** RenderEventManager.cpp
*/

#include "RenderEventDraw.hpp"

RenderEventManager::RenderEventManager()
{
    EventRegister->registerCallback(add);
    EventRegister->registerCallback(draw);
    EventRegister->registerCallback(update);
    EventRegister->registerCallback(remove);
}

RenderEventManager::~RenderEventManager()
{
    while (this->_list.size()) {
        delete this->_list[this->_list.size() - 1];
        this->_list.pop_back();
    }
}

void RenderEventManager::add(const RenderEventAdd *e)
{
    try {
        delete this->_list.at(e->_id);
    } catch (...) {
    }
    this->_list[e->_id] = e->_obj;
}

void RenderEventManager::draw(const RenderEventDraw *e)
{
    for (auto &it : this->_list)
        it->seconde->draw(e->_render);
}

void RenderEventManager::Remove(const RenderEventRemove *e)
{
    try {
        delete this->_list.at(e->_id);
    } catch (...) {
    }
}

void RenderEventManager::Update(const RenderEventUpdate *e)
{
    this->_list[e->_id] = e->_obj;
}
