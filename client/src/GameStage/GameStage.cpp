/*
** EPITECH PROJECT, 2021
** GameStage
** File description:
** GameStage.cpp
*/

#include "GameStage.hpp"

GameStage::GameStage()
{
}

GameStage::~GameStage()
{
}

std::size_t GameStage::getStageLvl() const
{
    return 0;
}

std::string GameStage::getStageBackground() const
{
    return "";
}

StageStep GameStage::getStageStep(bool move = true)
{
    return StageStep(EntityType::MAX_VALUE, 0, "", {0, 0});
}

std::queue<StageStep> GameStage::getStagePrevious(std::size_t nb) const
{
    return std::queue<StageStep>();
}

std::queue<StageStep> GameStage::getStageStepAt(std::size_t time, bool move = true)
{
    return std::queue<StageStep>();
}

std::string GameStage::getStageNext() const
{
    return "";
}