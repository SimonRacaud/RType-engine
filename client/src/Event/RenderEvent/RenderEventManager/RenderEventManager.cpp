/*
** EPITECH PROJECT, 2021
** RenderEventManager
** File description:
** RenderEventManager.cpp
*/

#include "RenderEventManager.hpp"

RenderEventManager::RenderEventManager()
{
    reg->registerCallback<RenderEventAdd<uniqueId>>([this] (const Engine::Event::IEvent *e) {
        this->add(static_cast<const RenderEventAdd<uniqueId> *>(e));
    });
    reg->registerCallback<RenderEventDraw>([this] (const Engine::Event::IEvent *e) {
        this->draw(static_cast<const RenderEventDraw *>(e));
    });
    reg->registerCallback<RenderEventUpdate<uniqueId>>([this] (const Engine::Event::IEvent *e) {
        this->update(static_cast<const RenderEventUpdate<uniqueId> *>(e));
    });
    reg->registerCallback<RenderEventRemove<uniqueId>>([this] (const Engine::Event::IEvent *e) {
        this->remove(static_cast<const RenderEventRemove<uniqueId> *>(e));
    });
}

RenderEventManager::~RenderEventManager()
{
    for (auto &it : this->_list)
        delete it.second;
    this->_list.clear();
}

void RenderEventManager::add(const RenderEventAdd<uniqueId> *e)
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
        it.second->draw(e->_render);
}

void RenderEventManager::remove(const RenderEventRemove<uniqueId> *e)
{
    try {
        delete this->_list.at(e->_id);
        this->_list.erase(e->_id);
    } catch (...) {
    }
}

void RenderEventManager::update(const RenderEventUpdate<uniqueId> *e)
{
    this->_list[e->_id] = e->_obj;
}
