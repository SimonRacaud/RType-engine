/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

#include "EngineCore.hpp"

namespace Component {
	struct Damage : public Engine::BaseComponent<Damage> {
		public:
			Damage(int damage) : _damage(damage) {}
			virtual ~Damage() = default;

			int _damage;
	};
}

#endif /* !DAMAGE_HPP_ */
