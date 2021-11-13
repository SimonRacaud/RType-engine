/*
** EPITECH PROJECT , 2021
** StartScene
** File description:
** \file StartScene.cpp
** \author simon
** \brief
** \date 04/11/2021
*/

#include "GameCore/GameCore.hpp"
#include "Entities/Button/Button.hpp"
#include "Entities/Player/Player.hpp"

#include "StartScene.hpp"
#include "Component/Render.hpp"
#include "Component/InputEvent.hpp"
#include "TextManager/TextManager.hpp"
#include "ShapeManager/ShapeManager.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "Entities/ImageView/ImageView.hpp"
#include "Entities/Label/Label.hpp"
#include "Item/vector2D.hpp"
#include "Event/MoveEvents/MoveHandler/MoveHandler.hpp"
#include "Systems/ColliderSystem/ColliderSystem.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;
extern std::unique_ptr<IEventManager<renderToolSfml>> event;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    ImageView image("asset/sprites/r-typesheet1.gif",
        vector2D(100, 100), vector2f(0.5, 0.5), this->getCluster());

    Label label(this->getCluster(), 42424242, vector2D(100, 10),
        vector2D(5, 5), color_e::GREEN);

    /// Select needed systems
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::LogPositionSystem,
        System::RenderSystem,
        System::InputEventSystem>();
}