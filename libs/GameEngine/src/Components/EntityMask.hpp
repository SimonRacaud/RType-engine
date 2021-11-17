/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityMask
*/

#ifndef ENTITYMASK_HPP_
#define ENTITYMASK_HPP_

#include "BaseComponent/BaseComponent.hpp"

namespace Component {
	enum MASK {
		EQUIPMENT,
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
