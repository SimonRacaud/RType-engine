/*
** EPITECH PROJECT , 2021
** HomeScene
** File description:
** \file HomeScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "HomeScene.hpp"
#include "GameCore/GameCore.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "Event/GUI/SelectScene.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

HomeScene::HomeScene() : Engine::AbstractScene<HomeScene>(ClusterName::HOME), _audio(GameCore::config->getVar<std::string>("MUSIC_HOME_SCENE"))
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, GameCore::config->getVar<int>("DEFAULT_VOLUME"));
}

void HomeScene::open()
{
    const std::string backgroundPath = GameCore::config->getVar<std::string>("HOME_BACKGROUND");
    const std::string subtitle = GameCore::config->getVar<std::string>("HOME_SUBTITLE");
    const std::string title = GameCore::config->getVar<std::string>("HOME_TITLE");
    const std::string mention = GameCore::config->getVar<std::string>("HOME_MENTIONS");
    const std::string playBtn = GameCore::config->getVar<std::string>("HOME_BTN_PLAY");
    const std::string optionBtn = GameCore::config->getVar<std::string>("HOME_BTN_OPTIONS");
    /// ENTITY CREATION
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1),
        this->getCluster());
    ImageView titleImg(title, vector2D(125, 180), vector2f(0.6, 0.6),
        this->getCluster());

    Label subTitleLabel(this->getCluster(), subtitle, vector2D(5, 5),
        vector2D(1, 1), color_e::GREEN);
    Label mentionLabel(this->getCluster(), mention, vector2D(290, 780),
        vector2D(1, 1), color_e::GREEN);

    Button playButton(this->getCluster(), playBtn, vector2D(280, 350), vector2f(3, 3),
        std::make_shared<SelectScene>(ClusterName::ROOM_LIST));
    Button OptionButton(this->getCluster(), optionBtn, vector2D(280, 475), vector2f(3, 3),
        std::make_shared<SelectScene>(ClusterName::SETTINGS));
    Button QuitButton(this->getCluster(), "Quit", vector2D(280, 600), vector2f(3, 3),
        std::make_shared<SelectScene>(ClusterName::GLOBAL));
    // EVENT SECTION
    GET_EVENT_REG.registerEvent<AudioEventStopAll>();
    GET_EVENT_REG.registerEvent<AudioEventPlay>(_audio);
    /// SYSTEM SELECTION
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}