/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Shooting
*/

#ifndef SHOOTING_HPP_
#define SHOOTING_HPP_

#include "EngineCore.hpp"

namespace Component {
	class Shooting : public Engine::BaseComponent<Shooting> {
		public:
			Shooting() = default;
			virtual ~Shooting() = default;

			bool _isCharging = false;
			bool _hasShot = false;

	};
}

#endif /* !SHOOTING_HPP_ */
