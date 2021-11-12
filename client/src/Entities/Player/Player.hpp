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
#include "vector2D.hpp"

class Player {
	public:
		Player(const vector2D &position, const vector2D &size, const vector2D &hitboxSize, const std::string &sprite);
		~Player();

	protected:
	private:
};

#endif /* !PLAYER_HPP_ */
