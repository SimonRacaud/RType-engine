/*
** EPITECH PROJECT, 2021
** GameStage
** File description:
** GameStage.cpp
*/

#include "GameStage.hpp"

GameStage::GameStage(const std::string &path) : _content(this->readFile(path))
{
    this->applyFormat();
    this->checkFormat();
    this->extract();
}

GameStage::GameStage(std::vector<std::string> file) : _content(file)
{
    this->applyFormat();
    this->checkFormat();
    this->extract();
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

StageStep GameStage::getStageStep(bool move)
{
    return StageStep(EntityType::MAX_VALUE, 0, "", {0, 0});
}

std::queue<StageStep> GameStage::getStagePrevious(std::size_t nb) const
{
    return std::queue<StageStep>();
}

std::queue<StageStep> GameStage::getStageStepAt(std::size_t time, bool move)
{
    return std::queue<StageStep>();
}

std::string GameStage::getStageNext() const
{
    return "";
}

void GameStage::extract()
{
}

void GameStage::applyFormat()
{
}

void GameStage::checkFormat() const
{
}

std::vector<std::string> GameStage::readFile(const std::string &) const
{
}