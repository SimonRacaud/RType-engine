/*
** EPITECH PROJECT, 2021
** RType
** File description:
** OutofBoundsSystem
*/

#ifndef OUTOFBOUNDSSYSTEM_HPP_
#define OUTOFBOUNDSSYSTEM_HPP_

#include "global.hpp"
#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "FactoryShortcuts.hpp"
#include "EntityManager/EntityManager.hpp"
#include "GameCore/GameCore.hpp"
#include "Component/Render.hpp"

namespace System {
	class OutofBoundsSystem : public Engine::AbstractSystem<OutofBoundsSystem> {
		public:
			OutofBoundsSystem();
			virtual ~OutofBoundsSystem() = default;

			void run(const std::vector<Engine::Entity> &entities) override;
	};
}

#endif /* !OUTOFBOUNDSSYSTEM_HPP_ */
