/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include <iostream>
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "Scene/Start/StartScene.hpp"
#include "Scene/Debug/DebugScene.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

using namespace std;

Engine::IGameEngine &engine = Engine::EngineFactory::getInstance();

int main(void)
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Position>();
    componentManager.registerComponent<Engine::Velocity>();
    componentManager.registerComponent<Engine::Timer>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<System::LogPositionSystem>();
    systemManager.registerSystem<Engine::TimerSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    sceneManager.registerScene<Scene::StartScene>();
    sceneManager.registerScene<Scene::DebugScene>("Mon paramètre de test");
    sceneManager.select<Scene::DebugScene>();

    engine.exec();
    return EXIT_SUCCESS;
}