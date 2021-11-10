/*
** EPITECH PROJECT , 2021
** StartScene
** File description:
** \file StartScene.cpp
** \author simon
** \brief
** \date 04/11/2021
*/

#include "StartScene.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    Engine::IEntityManager &entityManager = engine.getEntityManager();
    Engine::ComponentManager &componentManager = engine.getComponentManager();

    // Create entities here...

    /// Select needed systems
    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem>();
}