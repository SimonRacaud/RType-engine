/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerSystem
*/

#include "TimerSystem.hpp"
#include "FactoryShortcuts.hpp"
#include "EntityManager.hpp"
using namespace Engine;

TimerSystem::TimerSystem(float interval) : _interval(interval)
{
}

TimerSystem::~TimerSystem()
{
}

void TimerSystem::run()
{
	for (Entity e : this->getManagedEntities()) {
		auto timer = GET_COMP_M.get<Timer>(e);
		timer._currentTime -= _interval;
		if (timer._currentTime <= 0.0f) {
			timer._callback(timer._callbackEvent);
			timer.reset();
		}
	}
}

void TimerSystem::reset()
{
	for (Entity e : this->getManagedEntities()) {
		auto timer = GET_COMP_M.get<Timer>(e);
		timer.reset();
	}
}