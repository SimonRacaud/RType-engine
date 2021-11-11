/*
** EPITECH PROJECT , 2021
** SettingsScene
** File description:
** \file SettingsScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "SettingsScene.hpp"
#include "GameCore/GameCore.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

SettingsScene::SettingsScene()
    : Engine::AbstractScene<SettingsScene>(ClusterName::SETTINGS)
{
}

void SettingsScene::open()
{
    // <== create entities

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}