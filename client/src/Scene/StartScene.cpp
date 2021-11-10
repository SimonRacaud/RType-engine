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

    const std::function<void(Engine::Entity e)> testCallback = [] (Engine::Entity) {
        std::cout << "STD FUNCTION CALLBACK\n";
        engine.getEventRegister().registerEvent<TimerEvent>("hello");
    };

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);
    componentManager.add<Engine::Timer>(entity, static_cast<Engine::Time>(100), std::make_shared<std::function<void(Engine::Entity e)>>(testCallback), false);
    Engine::SystemManager &systemManager = engine.getSystemManager();


    std::function<void(const TimerEvent *e)> func = timerCallback;
    engine.getEventRegister().registerCallback(func);

    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, Engine::TimerSystem>();
    systemManager.getSystem<Engine::TimerSystem>().setInterval(static_cast<Engine::Time>(1000));
}

void StartScene::timerCallback(const TimerEvent *e)
{
    std::cout << "TIMER CALLBACK: " << e->_print << std::endl;
}