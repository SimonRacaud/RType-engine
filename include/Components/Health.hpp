/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include "BaseComponent/BaseComponent.hpp"

namespace Component {
	class Health : public Engine::BaseComponent<Health> {
		public:
			Health(int health) : _health(health) {}
			virtual ~Health() = default;

			int _health;
	};
}

#endif /* !HEALTH_HPP_ */
