/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"

#include <iostream>
#include "global.hpp"
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"

Engine::IGameEngine &ServerCore::engine = Engine::EngineFactory::getInstance();
std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{
}

void ServerCore::run(void)
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Timer>();
    componentManager.registerComponent<Component::Hitbox>();
    componentManager.registerComponent<Component::Position>();
    componentManager.registerComponent<Component::Velocity>();
    componentManager.registerComponent<Engine::ScoreComponent>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<Engine::TimerSystem>();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<Engine::ColliderSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    //sceneManager.registerScene<Scene::Example>();

    engine.exec();
}