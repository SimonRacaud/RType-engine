/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AddScoreEventManager
*/

#ifndef ADDSCOREEVENTMANAGER_HPP_
#define ADDSCOREEVENTMANAGER_HPP_

#include "GameCore/GameCore.hpp"
#include "Event/AddScore/AddScoreEvent.hpp"

void addScore(const AddScoreEvent *e);

class AddScoreEventManager {
	public:
		AddScoreEventManager();
		~AddScoreEventManager() = default;

};

#endif /* !ADDSCOREEVENTMANAGER_HPP_ */
