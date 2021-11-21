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
	std::vector<Engine::Entity> list;

    try {
		if (GET_COMP_M.get<Component::EntityMask>(e->_entity)._currentMask == Component::MASK::PLAYER) {
			componentManager.foreachComponent<Component::EntityMask>([&list, componentManager](std::unique_ptr<Component::EntityMask> &comp) {
				Engine::Entity e = componentManager.getOwner(*comp);
				list.push_back(e);
			});
			if (list.size() == 1) {
				GET_SCENE_M.select<Scene::EndGameScene>(true);
			}
		}
        if (GameCore::networkCore.isMaster()) {
            GameCore::networkCore.destroyEntity(GET_ENTITY_M.getNetworkId(e->_entity));
            GET_ENTITY_M.remove(e->_entity);
		}
    } catch (std::exception) {}
}