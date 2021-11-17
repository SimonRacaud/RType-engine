/*
** EPITECH PROJECT , 2021
** RoomListScene
** File description:
** \file RoomListScene.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "RoomListScene.hpp"

#include "GameCore/GameCore.hpp"
#include "Item/vector2D.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "Event/GUI/SelectPreviousScene.hpp"
#include "Event/GUI/SelectScene.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "System/NetworkReceive/NetworkReceiveSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

RoomListScene::RoomListScene()
    : Engine::AbstractScene<RoomListScene>(ClusterName::ROOM_LIST), _audio(GameCore::config->getVar<std::string>("MUSIC_ROOMLIST_SCENE"))
{
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, _audio);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(_audio, 100);
}

void RoomListScene::open()
{
    const std::string backgroundPath = GameCore::config->getVar<std::string>("HOME_BACKGROUND");
    const std::string listBackgroundPath = GameCore::config->getVar<std::string>("ROOM_BACKGROUND");
    const std::string mention = GameCore::config->getVar<std::string>("HOME_MENTIONS");
    // ENTITY CREATION
    // header
    ImageView background(backgroundPath, vector2D(0, 0), vector2f(1, 1),
        this->getCluster());
    Label title(this->getCluster(), "GAME ROOMS", vector2D(320, 20),
        vector2D(2, 2), color_e::GREEN);
    // body
    Button newGame(this->getCluster(), "NEW GAME", vector2D(20, 80),
        vector2f(2, 2), std::make_shared<SelectScene>(ClusterName::GAME)); // TODO button event
    // body - list
    ImageView listBack(listBackgroundPath, vector2D(50, 170), vector2f(1, 1),
        this->getCluster());

    std::vector<size_t> roomList = {0, 1, 2, 3, 42, 5}; // TODO get through the network
    this->reloadRoomList(roomList);

    Button refresh(this->getCluster(), "REFRESH", vector2D(320, 600),
        vector2f(2, 2), nullptr); // TODO button event
    // footer
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
        System::InputEventSystem,
        System::NetworkReceiveSystem>();
}

void RoomListScene::reloadRoomList(std::vector<size_t> const &roomIdList)
{
    // Clear the list
    GameCore::engine.getEntityManager().remove(ClusterName::ROOM_LIST_ITEMS);
    //
    size_t positionY = 180;
    size_t positionX = 320;
    size_t counter = 0;
    for (size_t id : roomIdList) {
        Button room(ClusterName::ROOM_LIST_ITEMS, "Room " + std::to_string(id),
            vector2D(positionX, positionY), vector2f(2, 2), nullptr); // TODO button event
        positionY += 60;
        counter++;
        if (counter == 7) {
            counter = 0;
            positionY = 180;
            positionX += 120;
        }
    }
}

void RoomListScene::close()
{
    AbstractScene<RoomListScene>::close();
    // destroy room list
    GameCore::engine.getEntityManager().remove(ClusterName::ROOM_LIST_ITEMS);
}