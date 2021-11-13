/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EnemyType
*/

#ifndef ENEMYTYPE_HPP_
#define ENEMYTYPE_HPP_

#include "EngineCore.hpp"

namespace Component {
	class EnemyType : public Engine::BaseComponent<EnemyType> {
		public:
			EnemyType(const float &moveSpeed, const float &shootingSpeed)
				: _maxMoveSpeed(moveSpeed), _shootingSpeed(shootingSpeed) {}
			virtual ~EnemyType() = default;

			float _maxMoveSpeed;
			float _shootingSpeed;
	};
}

#endif /* !ENEMYTYPE_HPP_ */
