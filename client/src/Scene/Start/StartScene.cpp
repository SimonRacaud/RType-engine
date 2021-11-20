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

#include "GameCore/GameCore.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "Event/GUI/SelectScene.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "Item/vector2D.hpp"

using namespace Scene;
using namespace std;
using namespace Engine;

extern Engine::IGameEngine &engine;
extern std::unique_ptr<IEventManager> event;

StartScene::StartScene(): AbstractScene<StartScene>(ClusterName::START), _audio(GameCore::config->getVar<std::string>("MUSIC_START_SCENE"))
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, GameCore::config->getVar<int>("DEFAULT_VOLUME"));
}

void StartScene::open()
{
    const std::string backgroundPath = GameCore::config->getVar<std::string>("HOME_BACKGROUND");
    const std::string title = GameCore::config->getVar<std::string>("HOME_TITLE");
    const std::string mention = GameCore::config->getVar<std::string>("HOME_MENTIONS");
    // ENTITY CREATION
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1),
        this->getCluster());
    ImageView titleImg(title, vector2D(90, 200), vector2f(0.7, 0.7),
        this->getCluster());

    Label mentionLabel(this->getCluster(), mention, vector2D(290, 780),
        vector2D(1, 1), color_e::GREEN);

    Button startButton(this->getCluster(), "Start", vector2D(280, 500),
        vector2f(3, 3), std::make_shared<SelectScene>(ClusterName::HOME));
    // EVENT SECTION
    GET_EVENT_REG.registerEvent<AudioEventPlay>(_audio);
    // SYSTEM SELECTION
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}