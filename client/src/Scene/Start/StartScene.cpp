/*
** EPITECH PROJECT , 2021
** StartScene
** File description:
** \file StartScene.cpp
** \author simon
** \brief
** \date 04/11/2021
*/

#include "StartScene.hpp"
#include "Component/Render.hpp"
#include "Component/InputEvent.hpp"
#include "TextManager/TextManager.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;
extern std::unique_ptr<IEventManager<renderToolSfml>> event;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    Engine::IEntityManager &entityManager = engine.getEntityManager();
    Engine::ComponentManager &componentManager = engine.getComponentManager();

    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    // Create entities here...

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);

    std::shared_ptr<TextManager> tmp = std::make_shared<TextManager>();
    tmp->setColor(ITextManager<renderToolSfml>::color_e::RED);
    tmp->setContent("mdr");
    tmp->setFont("asset/font/Code-Bold.ttf");
    componentManager.add<Engine::Render>(entity, tmp);

    componentManager.add<Engine::InputEvent>(entity, [](const Engine::Entity &) {
        auto pos = event->getMousePos();
        std::cout << "Mouse pos -> {" << pos.x << ", " << pos.y << "}" << std::endl;
    });

    /// Select needed systems
    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, System::RenderSystem, System::InputEventSystem>();
}