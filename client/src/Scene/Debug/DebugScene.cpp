/*
** EPITECH PROJECT , 2021
** DebugScene
** File description:
** \file DebugScene.cpp
** \author simon
** \brief
** \date 08/11/2021
*/

#include "DebugScene.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;

DebugScene::DebugScene(std::string testParam)
    : Engine::AbstractScene<DebugScene>(Engine::ClusterName::HOME)
{
    std::cerr << testParam << std::endl;
}

// Must be in an Entity's factory
static const auto destruct = [] (Engine::Entity entity, Engine::EntityName name,
                          Engine::ClusterName cluster) {
    std::cerr << "DESTROY " << entity << " " << (int)name << " " << (int)cluster << "\n";
};

void DebugScene::open()
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    Engine::IEntityManager &entityManager = engine.getEntityManager();

    /**
     * Entities (must be in an entity's factory)
     */
    Engine::Entity entity = entityManager.create(destruct, Engine::ClusterName::START, Engine::EntityName::EMPTY, true);
    entityManager.create(destruct, Engine::ClusterName::START, Engine::EntityName::TEST);
    Engine::Entity entity2 = entityManager.create(nullptr, Engine::ClusterName::GLOBAL, Engine::EntityName::TEST);

    /**
     * Network ID
     */
    // entityManager.setNetworkId(entity, 42);
    std::cerr << "Net Id = " << entityManager.getNetworkId(entity) << std::endl;

    /**
     * Components (must be in an entity's factory)
     */
    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Position>(entity2, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);

    //    try {
    //        entityManager.remove(Engine::EntityName::TEST);
    //    } catch (Engine::BasicException const &e) {
    //        std::cerr << "En error occurred\n";
    //    }

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem>();
    //systemManager.unregisterSystem<Engine::PhysicsSystem>();
    //systemManager.unregisterSystem<Engine::PhysicsSystem>();
}