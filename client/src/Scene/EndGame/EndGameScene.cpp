/*
** EPITECH PROJECT , 2021
** EndGameScene
** File description:
** \file EndGameScene.cpp
** \author simon
** \brief
** \date 18/11/2021
*/

#include "EndGameScene.hpp"

#include <sstream>
#include <iomanip>

#include "GameCore/GameCore.hpp"

#include "Event/GUI/SelectScene.hpp"

#include "Entities/Button/Button.hpp"
#include "Entities/Label/Label.hpp"
#include "Entities/ImageView/ImageView.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

using namespace Scene;
using namespace Engine;
using namespace std;

EndGameScene::EndGameScene() :
      Engine::AbstractScene<EndGameScene>(ClusterName::GAME_END)
{
    _scores.resize(GameCore::config->getVar<int>("MAX_CLIENT_ROOM"));
    std::fill(_scores.begin(), _scores.end(), 0);
}

void EndGameScene::open()
{
    this->_isFail = true;
    Label title(this->getCluster(), "GAME OVER", vector2D(230, 20),
        vector2D(4, 4), color_e::GREEN);

    if (this->_isFail) {
        Label subTitle(this->getCluster(), "YOU FAILED !", vector2D(310, 100),
            vector2D(2, 2), color_e::GREEN);
    } else {
        Label subTitle(this->getCluster(), "YOU WIN !", vector2D(320, 100),
            vector2D(2, 2), color_e::GREEN);
    }

    // Display score

    size_t positionY = 250;
    for (size_t i = 0; i < _scores.size(); i++) {
        std::stringstream stream;
        stream << "Player " << i + 1 << " score: " << std::setw(8) << std::setfill('0') << _scores[i];

        Label subTitle(this->getCluster(), stream.str(), vector2D(310, positionY + (i * 80)),
            vector2D(1, 1), color_e::GREEN);
    }
    //
    Button startButton(this->getCluster(), "MENU", vector2D(320, 710),
        vector2f(2, 2), std::make_shared<SelectScene>(ClusterName::HOME));
    // SYSTEM SELECTION
    Engine::SystemManager &systemManager = GameCore::engine.getSystemManager();
    systemManager.selectSystems<
        System::RenderSystem,
        System::InputEventSystem>();
}

void EndGameScene::setInput(const std::vector<size_t> &scores, size_t myScoreIndex, bool isFail)
{
    this->_scores = scores;
    this->_myScoreIndex = myScoreIndex;
    this->_isFail = isFail;
}

void EndGameScene::setPlayerScore(size_t const &score, const size_t &pos)
{
    if (pos != 0)
        this->_scores[pos - 1] = score;
}

void EndGameScene::setFail(bool isFail)
{
    this->_isFail = isFail;
}