/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ColliderSystem
*/

#ifndef COLLIDERSYSTEM_HPP_
#define COLLIDERSYSTEM_HPP_

#include "global.hpp"
#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Components/Hitbox.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "FactoryShortcuts.hpp"
#include "EntityManager/EntityManager.hpp"

namespace Engine {
	class ColliderSystem : public AbstractSystem<ColliderSystem> {
		public:
			ColliderSystem();
			virtual ~ColliderSystem() = default;

			void run(const vector<Entity> &entities) override;
	};
}

#endif /* !COLLIDERSYSTEM_HPP_ */
