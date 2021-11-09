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

DebugScene::DebugScene()
    : Engine::AbstractScene<DebugScene>(Engine::ClusterName::HOME)
{}

void DebugScene::open()
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    Engine::IEntityManager &entityManager = engine.getEntityManager();

//    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::GLOBAL, Engine::EntityName::TEST);
//
//    componentManager.add<Engine::Position>(entity, 10, 10);
//    componentManager.add<Engine::Velocity>(entity, 1, 0);

    Engine::SystemManager &systemManager = engine.getSystemManager();

    systemManager.selectSystems<System::LogPositionSystem>();
    std::cerr << "OPEN DEBUG SCENE" << std::endl;
}