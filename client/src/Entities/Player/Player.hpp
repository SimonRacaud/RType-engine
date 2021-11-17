/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
#include "GameCore/GameCore.hpp"
#include "Event/IEvent.hpp"
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "Item/vector2D.hpp"
#include "Item/vector2f.hpp"

using Engine::ClusterName;

float lerp(float minValue, float maxValue, float norm);

class Player {
	public:
        Player(ClusterName cluster, int playerNumber, const vector2D &position,
            const vector2D &velocity = {0, 0});
		~Player() = default;

        void setNetworkId(uint32_t entityId);
        Engine::Entity getId() const;

	protected:
      void configAppearance(Engine::Entity entity, vector2D const &position,
          Engine::ComponentManager &componentManager, int playerNumber);
      void configEvent(Engine::Entity entity, Engine::ComponentManager &componentManager);

	private:
		static void hit(Engine::ClusterName cluster, Engine::Entity a, Engine::Entity b);
		static bool animationPlayer(Engine::ClusterName cluster, Engine::Entity once);
	
    private:
        Engine::Entity _entity;
};

#endif /* !PLAYER_HPP_ */
