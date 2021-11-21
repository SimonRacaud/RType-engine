/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AddScoreEventManager
*/

#include "AddScoreEventManager.hpp"
#include "Scene/EndGame/EndGameScene.hpp"

AddScoreEventManager::AddScoreEventManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const AddScoreEvent *)>(addScore));
}

void addScore(const AddScoreEvent *e)
{
	Scene::EndGameScene *ptr = reinterpret_cast<Scene::EndGameScene *>(&GET_SCENE_M.get<Scene::EndGameScene>());
	auto scoreComp = GET_COMP_M.get<Engine::ScoreComponent>(e->_entity);
	ptr->setPlayerScore(scoreComp.value, scoreComp.playerNumber);
}
