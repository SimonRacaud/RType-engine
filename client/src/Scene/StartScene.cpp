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
#include "System/LogPositionSystem.hpp"
#include "TimerEvent.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    Engine::IEntityManager &entityManager = engine.getEntityManager();

    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);
    componentManager.add<Engine::Timer<TimerEvent>>(entity, 100, "Hello World");
    Engine::SystemManager &systemManager = engine.getSystemManager();
    GET_EVENT_REG.registerCallback<TimerEvent>(Engine::EventCallbackSignature(timerCallback));

    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, Engine::TimerSystem>();
    systemManager.getSystem<Engine::TimerSystem>().setInterval(1);
}

void StartScene::timerCallback(const TimerEvent *e)
{
    std::cout << e->_print << std::endl;
}