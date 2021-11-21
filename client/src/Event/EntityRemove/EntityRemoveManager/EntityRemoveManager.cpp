/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveManager
*/

#include "EntityRemoveManager.hpp"
#include "Scene/EndGame/EndGameScene.hpp"

EntityRemoveManager::EntityRemoveManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const EntityRemoveEvent *e)>(entityRemove));
}


void entityRemove(const EntityRemoveEvent *e)
{
	Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();

    try {
        if (GameCore::networkCore.isMaster()) {
            GameCore::networkCore.destroyEntity(GET_ENTITY_M.getNetworkId(e->_entity));
            GET_ENTITY_M.remove(e->_entity);
        }
		if (GET_COMP_M.get<Component::EntityMask>(e->_entity)._currentMask == Component::MASK::PLAYER) {
            size_t counter = 0;
			componentManager.foreachComponent<Engine::ScoreComponent>([&counter](Engine::ScoreComponent *) {
				counter++;
			});
			if (counter == 0) {
				GET_SCENE_M.select<Scene::EndGameScene>(true);
			}
		}
    } catch (std::exception const &e) {
        std::cerr << "entityRemove " << e.what() << std::endl;
    }
}