/*
** EPITECH PROJECT , 2021
** HomeScene
** File description:
** \file HomeScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "HomeScene.hpp"
#include "GameCore/GameCore.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

HomeScene::HomeScene() : Engine::AbstractScene<HomeScene>(ClusterName::HOME)
{}

void HomeScene::open()
{
    // <== create entities

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}