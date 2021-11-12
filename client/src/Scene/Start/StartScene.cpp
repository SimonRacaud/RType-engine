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
#include "Event/MoveEvents/MoveHandler/MoveHandler.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;
extern std::unique_ptr<IEventManager<renderToolSfml>> event;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    // Create entities here...

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);

    std::shared_ptr<TextManager> tmp = std::make_shared<TextManager>();
    tmp->setColor(color_e::RED);
    tmp->setContent("mdr");
    tmp->setFont("asset/font/Code-Bold.ttf");
    componentManager.add<Engine::Render>(entity, tmp);

    componentManager.add<Engine::InputEvent>(entity, [](const Engine::Entity &) {
        auto pos = GameCore::event->getMousePos();
        //std::cout << "Mouse pos -> {" << pos.x << ", " << pos.y << "}" << std::endl;
    });

    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/R_Type-01_theme.ogg");
    GET_EVENT_REG.registerEvent<AudioEventVolume>("asset/music/R_Type-01_theme.ogg", 100);
    Button test("button", {110, 110}, {1, 1}, std::make_shared<AudioEventPlay>("asset/music/R_Type-01_theme.ogg"));
    Player popo({40, 40}, {40, 40}, {40, 40}, "asset/gui/button_pressed.png");

    // other
    entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);
    componentManager.add<Engine::Position>(entity, 20, 20);
    std::shared_ptr<ShapeManager> tmp2 = std::make_shared<ShapeManager>(vector2D(200, 200), vector2D(20, 20), color_e::GREEN);
    componentManager.add<Engine::Render>(entity, tmp2);

    /// Select needed systems
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, System::RenderSystem, System::InputEventSystem>();
}