/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveManager
*/

#include "EntityRemoveManager.hpp"
#include "Scene/EndGame/EndGameScene.hpp"
#include "Event/AddScore/AddScoreEvent.hpp"
#include "Event/NetworkEvent/QuitEvent.hpp"

EntityRemoveManager::EntityRemoveManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const EntityRemoveEvent *e)>(entityRemove));
}


void entityRemove(const EntityRemoveEvent *e)
{
	Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();

    try {
		if (GET_COMP_M.get<Component::EntityMask>(e->_entity)._currentMask == Component::MASK::PLAYER) {
			Scene::EndGameScene *ptr = reinterpret_cast<Scene::EndGameScene *>(&GET_SCENE_M.get<Scene::EndGameScene>());
			auto scoreComp = GET_COMP_M.get<Engine::ScoreComponent>(e->_entity);
			ptr->setPlayerScore(scoreComp.value, scoreComp.playerNumber);
            size_t counter = 0;
			componentManager.foreachComponent<Engine::ScoreComponent>([&counter](Engine::ScoreComponent *) {
				counter++;
			});
			if (counter == 1) {
				GET_SCENE_M.select<Scene::EndGameScene>(true);
				GET_EVENT_REG.registerEvent<QuitEvent>();
			}
		}
        if (GameCore::networkCore.isMaster()) {
            GameCore::networkCore.destroyEntity(GET_ENTITY_M.getNetworkId(e->_entity));
            GET_ENTITY_M.remove(e->_entity);
        }
    } catch (std::exception const &e) {
        std::cerr << "entityRemove " << e.what() << std::endl;
    }
}