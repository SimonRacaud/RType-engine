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
#include "Scene/StartScene.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

using namespace std;

Engine::IGameEngine &engine = Engine::EngineFactory::getInstance();

int main(void)
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Position>();
    componentManager.registerComponent<Engine::Velocity>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<System::LogPositionSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    sceneManager.registerScene<Scene::StartScene>();
    sceneManager.select<Scene::StartScene>();

    engine.exec();
    return EXIT_SUCCESS;
}