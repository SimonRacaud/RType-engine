/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
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

	protected:
	private:
};

#endif /* !PLAYER_HPP_ */
