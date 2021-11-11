/*
** EPITECH PROJECT , 2021
** RoomListScene
** File description:
** \file RoomListScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "RoomListScene.hpp"
#include "GameCore/GameCore.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

RoomListScene::RoomListScene()
    : Engine::AbstractScene<RoomListScene>(ClusterName::ROOM_LIST)
{}

void RoomListScene::open()
{
    // <== create entities

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}