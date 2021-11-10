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
	this->setRequirements<Timer>();
}

TimerSystem::~TimerSystem()
{
}

void TimerSystem::run()
{
	for (Entity e : this->getManagedEntities()) {
		auto timer = GET_COMP_M.get<Timer>(e);
		if (timer._countdown) {
			timer._currentTime -= _interval;
			if (timer._currentTime.count() <= 0) {
				timer._eventFactory->operator()(e);
				timer._currentTime = timer._maxTime;
			}
		} else {
			auto now = Clock::now();
			if (now - timer._startTime >= timer._maxTime) {
				timer._eventFactory->operator()(e);
				timer._startTime = now;
			}
		}
	}
}

void TimerSystem::setInterval(const Time &interval)
{
	_interval = interval;
}