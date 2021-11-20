/*
** EPITECH PROJECT, 2021
** EmptyClusterManager
** File description:
** EmptyClusterManager.cpp
*/

#include "GameCore/GameCore.hpp"
#include "Event/EmptyCluster/EmptyClusterManager/EmptyClusterManager.hpp"

EmptyClusterManager::EmptyClusterManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();

    reg.registerCallback<EmptyCluster>([] (const Engine::Event::IEvent *e) {
        EmptyClusterManager::doWork(static_cast<const EmptyCluster *>(e));
    });
}

void EmptyClusterManager::doWork(const EmptyCluster *e)
{
    try {
        GameCore::engine.getEntityManager().remove(e->_cluster);
        if (e->_func)
            e->_func();
    } catch (std::exception const &e) {
        std::cerr << "EmptyClusterManager::doWork " << e.what() << std::endl;
    }
}