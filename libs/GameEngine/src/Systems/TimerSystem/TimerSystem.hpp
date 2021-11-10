/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerSystem
*/

#ifndef TIMERSYSTEM_HPP_
#define TIMERSYSTEM_HPP_

#include "global.hpp"
#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Components/Timer.hpp"
#include "EntityManager/EntityManager.hpp"
#include <list>

namespace Engine {
	class TimerSystem : public AbstractSystem<TimerSystem> {
		public:
			TimerSystem();
			~TimerSystem();

			/**
			 * @brief Updates all active timers by a time
			 * 
			 * @param ms Time to update each timer with
			 */
			void run() override;

			/**
			 * @brief Resets all active timers to 0
			 *
			 */
			void reset();

			/**
			 * @brief Set the Interval object
			 * 
			 * @param interval 
			 */
			void setInterval(const float &interval);
		private:
			float _interval;
	};
}

#endif /* !TIMERSYSTEM_HPP_ */
