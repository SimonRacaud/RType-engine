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
#include "Entities/Bullet/Bullet.hpp"
#include "Entities/ScrollingBackground/ScrollingBackground.hpp"

#include "StartScene.hpp"
#include "Component/Render.hpp"
#include "Component/InputEvent.hpp"
#include "TextManager/TextManager.hpp"
#include "ShapeManager/ShapeManager.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "System/ScrollSystem/ScrollSystem.hpp"
#include "Entities/ImageView/ImageView.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/Enemy/Enemy.hpp"
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
    /*ImageView image("asset/sprites/r-typesheet1.gif",
        vector2D(100, 100), vector2f(0.5, 0.5), this->getCluster());

    Label label(this->getCluster(), 42424242, vector2D(100, 10),
        vector2D(5, 5), color_e::GREEN);

    /// Select needed systems
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::LogPositionSystem,
        System::RenderSystem,
        System::InputEventSystem>();*/

    /*Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();

    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    // Create entities here...

    Bullet(vector2D(100, 100));
    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);

    std::shared_ptr<TextManager> tmp = std::make_shared<TextManager>();
    tmp->setColor(color_e::RED);
    tmp->setContent("mdr");
    tmp->setFont("asset/font/Code-Bold.ttf");
    componentManager.add<Engine::Render>(entity, tmp);

    componentManager.add<Engine::InputEvent>(entity, [](const Engine::Entity &) {
        auto pos = GameCore::event->getMousePos();
        std::cout << "Mouse pos -> {" << pos.x << ", " << pos.y << "}" << std::endl;
    });

    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/R_Type-01_theme.ogg");
    GET_EVENT_REG.registerEvent<AudioEventVolume>("asset/music/R_Type-01_theme.ogg", 100);
    Button test("button", {110, 110}, {1, 1}, {1, 1}, std::make_shared<AudioEventPlay>("asset/music/R_Type-01_theme.ogg"));

    // other
    entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);
    componentManager.add<Engine::Position>(entity, 20, 20);
    std::shared_ptr<ShapeManager> tmp2 = std::make_shared<ShapeManager>(vector2D(200, 200), vector2D(20, 20), color_e::GREEN);
    componentManager.add<Engine::Render>(entity, tmp2);

    /// Select needed systems
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, System::RenderSystem, System::InputEventSystem, Engine::ColliderSystem>();*/

    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/R_Type-01_theme.ogg");
    GET_EVENT_REG.registerEvent<AudioEventVolume>("asset/music/R_Type-01_theme.ogg", 100);

    ScrollingBackground background(this->getCluster());
    Button test("button", {110, 110}, {1, 1}, std::make_shared<AudioEventPlay>("asset/music/R_Type-01_theme.ogg"));

    Enemy enemy(this->getCluster(), vector2D(200, 200), vector2D(1, 0), vector2f(1, 1), "asset/sprites/r-typesheet42.gif", 3, surface(vector2D(33, 18), vector2D(33, 18)));

    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, System::RenderSystem, System::InputEventSystem, System::ScrollSystem>();
}