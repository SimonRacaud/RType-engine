/*
** EPITECH PROJECT , 2021
** SettingsScene
** File description:
** \file SettingsScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "SettingsScene.hpp"

#include "GameCore/GameCore.hpp"
#include "Item/vector2D.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "Event/GUI/SelectPreviousScene.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

SettingsScene::SettingsScene()
    : Engine::AbstractScene<SettingsScene>(ClusterName::SETTINGS), _audio(GameCore::config->getVar<std::string>("MUSIC_SETTINGS_SCENE"))
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, 100);
}

void SettingsScene::open()
{
    const std::string backgroundPath = GameCore::config->getVar<std::string>("HOME_BACKGROUND");
    const std::string mention = GameCore::config->getVar<std::string>("HOME_MENTIONS");
    // ENTITY CREATION
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1),
        this->getCluster());

    Label title(this->getCluster(), "Settings", vector2D(320, 20),
        vector2D(2, 2), color_e::GREEN);
    Label mentionLabel(this->getCluster(), mention, vector2D(290, 780),
        vector2D(1, 1), color_e::GREEN);

    Button startButton(this->getCluster(), "Back", vector2D(20, 710),
        vector2f(2, 2), std::make_shared<SelectPreviousScene>());
    // EVENT SECTION
    GET_EVENT_REG.registerEvent<AudioEventPlay>(_audio);
    // SYSTEM SELECTION
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}