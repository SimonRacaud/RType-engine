/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityMask
*/

#ifndef ENTITYMASK_HPP_
#define ENTITYMASK_HPP_

#include "EngineCore.hpp"

namespace Component {
	enum MASK {
		PLAYER,
		BULLET,
		ENEMY,
	};

	class EntityMask : public Engine::BaseComponent<EntityMask> {
		public:
			EntityMask(MASK mask) : _currentMask(mask) {}
			virtual ~EntityMask() = default;

			MASK _currentMask;
	};
}

#endif /* !ENTITYMASK_HPP_ */
