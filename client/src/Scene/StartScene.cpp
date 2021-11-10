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

    // const std::function<void(Engine::Entity e)> testCallback = [] (Engine::Entity) {
    // };

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);
    componentManager.add<Engine::Timer>(entity, 100, nullptr);

    Engine::SystemManager &systemManager = engine.getSystemManager();
    Engine::Event::EventCallbackRegister &eventRegister = engine.getEventRegister();

    std::function<void(const TimerEvent *e)> func = timerCallback;
    engine.getEventRegister().registerCallback(func);
    std::string n = "hello";
    eventRegister.registerEvent<TimerEvent>(n);

    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, Engine::TimerSystem>();
    systemManager.getSystem<Engine::TimerSystem>().setInterval(1);
}

void StartScene::timerCallback(const TimerEvent *e)
{
    std::cout << e->_print << std::endl;
}