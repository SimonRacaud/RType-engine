/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerSystem
*/

#include "TimerSystem.hpp"
#include "FactoryShortcuts.hpp"

using namespace Engine;

static const Engine::Time freq = static_cast<Engine::Time>(1000);
static const SystemPriority priority = SystemPriority::HIGH;

TimerSystem::TimerSystem(float interval) : AbstractSystem<TimerSystem>(freq, priority), _interval(interval)
{
	this->setRequirements<Timer>();
}

TimerSystem::~TimerSystem()
{
}

void TimerSystem::run(const vector<Entity> &entities)
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