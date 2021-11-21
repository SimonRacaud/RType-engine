/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveManager
*/

#include "EntityRemoveManager.hpp"
#include "Scene/Game/GameScene.hpp"

EntityRemoveManager::EntityRemoveManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const EntityRemoveEvent *e)>(entityRemove));
}


void entityRemove(const EntityRemoveEvent *e)
{
    try {
        if (GameCore::networkCore.isMaster()) {
            Scene::GameScene &scene = *reinterpret_cast<Scene::GameScene *>(
                &GameCore::engine.getSceneManager().get<Scene::GameScene>());
            Time startTime = scene.getTimeStart();
            Time now = GET_NOW;
            if (now - startTime > 5000) {
                GameCore::networkCore.destroyEntity(GET_ENTITY_M.getNetworkId(e->_entity));
            }
        }
    } catch (std::exception) {}
}