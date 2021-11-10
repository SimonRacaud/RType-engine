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
#include "TextManager/TextManager.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

using namespace Scene;

extern Engine::IGameEngine &engine;

StartScene::StartScene()
    : Engine::AbstractScene<StartScene>(Engine::ClusterName::START)
{}

void StartScene::open()
{
    Engine::ComponentManager &componentManager = engine.getComponentManager();
    Engine::IEntityManager &entityManager = engine.getEntityManager();

    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    componentManager.add<Engine::Position>(entity, 10, 10);
    componentManager.add<Engine::Velocity>(entity, 1, 0);

    std::shared_ptr<TextManager> tmp = std::make_shared<TextManager>();
    tmp->setColor(ITextManager<renderToolSfml>::color_e::RED);
    tmp->setContent("mdr");
    tmp->setFont("asset/font/Code-Bold.ttf");
    componentManager.add<Engine::Render>(entity, tmp);

    Engine::SystemManager &systemManager = engine.getSystemManager();

    systemManager.selectSystems<Engine::PhysicsSystem, System::LogPositionSystem, System::RenderSystem>();
}