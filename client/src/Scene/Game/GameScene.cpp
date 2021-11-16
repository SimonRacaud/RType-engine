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

#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"
#include "Entities/Player/Player.hpp"
#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ScrollingBackground/ScrollingBackground.hpp"
#include "Entities/Progress/ProgressBar.hpp"

#include "Component/Render.hpp"
#include "TextManager/TextManager.hpp"
#include "Event/GUI/SelectPreviousScene.hpp"
#include "Event/EmptyCluster/EmptyCluster.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "System/ScrollSystem/ScrollSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

GameScene::GameScene()
    : Engine::AbstractScene<GameScene>(ClusterName::GAME), _audio(GameCore::config->getVar<std::string>("MUSIC_GAME_SCENE"))
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, 100);
}

void GameScene::open()
{
    vector2D win = GameCore::config->getVar<vector2D>("WINDOW_SIZE");
    const std::string waitText = GameCore::config->getVar<std::string>("CLIENT_WAIT_LABEL");
    const std::string backgroundPath = GameCore::config->getVar<std::string>("CLIENT_WAIT_BACKGROUND");

    // ENTITY CREATE
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1), this->getCluster());
    Button back(this->getCluster(), "Quit", vector2D(win.x / 2, win.y / 1.5), vector2f(1, 1), nullptr);

    // MANUAL COMPONENT BUILD
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity dynamicText = entityManager.create(nullptr, this->getCluster(), Engine::EntityName::EMPTY);
    std::string font = GameCore::config->getVar<string>("FONT");
    vector2D position((win.x - waitText.length() * 15) / 2, win.y / 2);

    componentManager.add<Engine::Render>(dynamicText, std::make_shared<TextManager>(position, vector2D(), color_e::WHITE, waitText, font));
    componentManager.add<Engine::Position>(dynamicText, (float)position.x, (float)position.y);

    ::Time timeUntilStart = !this->_timestampStart ? 0 : (GET_NOW - this->_timestampStart);
    Engine::Entity startGame = entityManager.create(nullptr, this->getCluster(), Engine::EntityName::EMPTY);
    componentManager.add<Engine::Timer>(startGame, std::chrono::milliseconds(timeUntilStart), [this, timeUntilStart](Engine::Entity) {
        GET_EVENT_REG.registerEvent<EmptyCluster>(this->getCluster(), [this]() {
            this->initGame();
        });
    });
    componentManager.add<Engine::Timer>(dynamicText, std::chrono::milliseconds(1000), [this, waitText, win, timeUntilStart](Engine::Entity a) {
        static size_t i = (timeUntilStart / 1000);
        Engine::Position &pos = GET_COMP_M.get<Engine::Position>(a);
        Engine::Render &render = GET_COMP_M.get<Engine::Render>(a);
        std::string str(waitText + std::to_string(i));

        pos.x = (win.x - str.length() * 15) / 2;
        dynamic_cast<TextManager *>(render._src[0].get())->setContent(str);
        i--;
    });

    // SYSTEM SELECT
    GameCore::engine.getSystemManager().selectSystems<System::RenderSystem, System::InputEventSystem, Engine::TimerSystem, System::RenderSystem>();
}

void GameScene::initGame() const
{
    // ENTITY CREATE
    ScrollingBackground background(this->getCluster());
    Player player(this->getCluster(), {120, 80}, {10, 10}, {40, 40}, "asset/sprites/r-typesheet1.gif");
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
    // EVENT SECTION
    GET_EVENT_REG.registerEvent<AudioEventPlay>(_audio);
    // SYSTEM SELECT
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        Engine::PhysicsSystem,
        System::RenderSystem,
        System::InputEventSystem,
        System::ScrollSystem>();
}

void GameScene::setTimeStart(::Time timestamp)
{
    this->_timestampStart = timestamp;
}