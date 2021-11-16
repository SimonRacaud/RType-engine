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

class Player {
	public:
		Player(ClusterName cluster, const vector2D &position,
          const vector2f &size, const vector2D &hitboxSize,
          const std::string &sprite);
		~Player();

        void setNetworkId(uint32_t entityId);

	protected:
	private:
		static void hit(Engine::ClusterName cluster, Engine::Entity a, Engine::Entity b);
		static bool animationPlayer(Engine::ClusterName cluster, Engine::Entity once);
	
    private:
        Engine::Entity _entity;
};

#endif /* !PLAYER_HPP_ */
