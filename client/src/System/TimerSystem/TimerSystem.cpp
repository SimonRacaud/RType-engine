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

TimerSystem::TimerSystem() : AbstractSystem<TimerSystem>(freq, priority)
{
	this->setRequirements<Timer>();
}

TimerSystem::~TimerSystem()
{
}

void TimerSystem::run(const vector<Entity> &entities)
{
	for (Entity e : entities) {
		auto &timer = GET_COMP_M.get<Timer>(e);
		if (timer._countdown) {
			timer._currentTime -= timer._interval;
			if (timer._currentTime.count() <= 0) {
				timer._eventFactory.operator()(e);
				timer._currentTime = timer._maxTime;
			}
		} else {
			std::chrono::steady_clock::time_point now = Clock::now();
			auto nb = now.time_since_epoch() - timer._startTime.time_since_epoch();
			if (nb >= timer._maxTime) {
				timer._eventFactory.operator()(e);
				timer._startTime = now;
			}
		}
	}
}