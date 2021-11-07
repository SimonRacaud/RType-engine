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

TimerSystem::TimerSystem() : AbstractSystem<TimerSystem>(freq, priority), _interval(0)
{
	this->setRequirements<BaseTimer>();
}

TimerSystem::~TimerSystem()
{
}

void TimerSystem::run()
{
	for (Entity e : this->getManagedEntities()) {
		auto timer = GET_COMP_M.get<BaseTimer>(e);
		timer._currentTime -= _interval;
		if (timer._currentTime <= 0.0f) {
			timer.exec();
			timer.reset();
		}
	}
}

void TimerSystem::reset()
{
	for (Entity e : this->getManagedEntities()) {
		auto timer = GET_COMP_M.get<BaseTimer>(e);
		timer.reset();
	}
}

void TimerSystem::setInterval(const float &interval)
{
	_interval = interval;
}