/*
** EPITECH PROJECT , 2021
** GameScene
** File description:
** \file GameScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "GameScene.hpp"
#include "GameCore/GameCore.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

GameScene::GameScene()
    : Engine::AbstractScene<GameScene>(ClusterName::GAME)
{}

void GameScene::open()
{
    // <== create entities

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::RenderSystem,
        System::InputEventSystem>();
}