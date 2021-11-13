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
#include "Item/vector2D.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ScrollingBackground/ScrollingBackground.hpp"
#include "Entities/Progress/ProgressBar.hpp"

#include "Event/GUI/SelectPreviousScene.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "System/ScrollSystem/ScrollSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

GameScene::GameScene()
    : Engine::AbstractScene<GameScene>(ClusterName::GAME)
{}

void GameScene::open()
{
    // ENTITY CREATE
    ScrollingBackground background(this->getCluster());
    Button back(this->getCluster(), "Quit", vector2D(5, 5), vector2f(2, 2),
        nullptr);
    Label numberPlayer(this->getCluster(), "0 P -", vector2D(10, 770),
        vector2D(1, 1), color_e::GREEN, EntityName::NB_PLAYER);
    Label playerScore(this->getCluster(), "000", vector2D(200, 770),
        vector2D(1, 1), color_e::GREEN, EntityName::SCORE);
    Label playerHighScore(this->getCluster(), "HI - 000", vector2D(350, 770),
        vector2D(1, 1), color_e::GREEN, EntityName::H_SCORE);
    Label beam(this->getCluster(), "BEAM", vector2D(195, 740),
        vector2D(1, 1), color_e::GREEN);
    ProgressBar beamPower(this->getCluster(), EntityName::BEAM_PROGRESS,
        vector2D(250, 742), vector2D(300, 15), color_e::BLUE, color_e::WHITE);
    // SYSTEM SELECT
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::RenderSystem,
        System::InputEventSystem,
        System::ScrollSystem>();
}