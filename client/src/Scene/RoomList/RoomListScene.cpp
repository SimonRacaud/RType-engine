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
#include "Item/vector2D.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "Event/GUI/SelectPreviousScene.hpp"
#include "Event/GUI/SelectScene.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

RoomListScene::RoomListScene()
    : Engine::AbstractScene<RoomListScene>(ClusterName::ROOM_LIST)
{}

void RoomListScene::open()
{
    const std::string backgroundPath = GameCore::config->getVar<std::string>("HOME_BACKGROUND");
    const std::string listBackgroundPath = GameCore::config->getVar<std::string>("ROOM_BACKGROUND");
    const std::string mention = GameCore::config->getVar<std::string>("HOME_MENTIONS");
    // ENTITY CREATION
    // header
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1),
        this->getCluster());
    Label title(this->getCluster(), "GAME ROOMS", vector2D(320, 20),
        vector2D(2, 2), color_e::GREEN);
    // body
    Button newGame(this->getCluster(), "NEW GAME", vector2D(20, 80),
        vector2f(2, 2), std::make_shared<SelectScene>(ClusterName::ROOM_LIST));
    ImageView listBack(listBackgroundPath, vector2D(50, 170), vector2f(1, 1),
        this->getCluster());

    // footer
    Label mentionLabel(this->getCluster(), mention, vector2D(290, 780),
        vector2D(1, 1), color_e::GREEN);
    Button startButton(this->getCluster(), "Back", vector2D(20, 710),
        vector2f(2, 2), std::make_shared<SelectPreviousScene>());
    // SYSTEM SELECTION
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}