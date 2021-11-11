/*
** EPITECH PROJECT, 2021
** GameStage
** File description:
** GameStage.cpp
*/

#include <regex>
#include <fstream>
#include "GameStage.hpp"

GameStage::GameStage(const std::string &path) : _content(this->readFile(path))
{
    if (!this->_content.size())
        throw std::invalid_argument("Empty file content");
    this->applyFormat();
    this->checkFormat();
    this->extract();
    this->sort();
}

GameStage::GameStage(std::vector<std::string> file) : _content(file)
{
    if (!this->_content.size())
        throw std::invalid_argument("Empty file content");
    this->applyFormat();
    this->checkFormat();
    this->extract();
    this->sort();
}

GameStage::~GameStage()
{
}

std::size_t GameStage::getStageLvl() const
{
    return this->_header.lvl;
}

std::string GameStage::getStageBackground() const
{
    return this->_header.background;
}

bool GameStage::isStageEnd() const
{
    return false;
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
    return this->_ended.nextStage;
}

void GameStage::sort()
{
}

void GameStage::extract()
{
}

void GameStage::applyFormat()
{
    std::string::iterator next;

    for (auto &line : this->_content) {
        for (std::string::iterator it = line.begin(); it != line.end();) {
            next = it + 1;
            if (*it == ' ' && it == line.begin()) {
                line.erase(it);
            } else if (*it == ' ' && next == line.end()) {
                line.erase(it);
            } else if (*it == ' ' && *next == ' ') {
                line.erase(it);
            } else
                it++;
        }
    }
}

void GameStage::checkFormat() const
{
    // Orignial regex -> ^XXXX "[0-9a-zA-Z\/_\-\.]*" [0-9]*$
    if (GameStage::matchWithRegex(this->_content[0], "^XXXX \"[0-9a-zA-Z\\/_\\-\\.]*\" [0-9]*$"))
        throw std::invalid_argument("Invalid line header (l. 0)");
    for (size_t y = 1; y < this->_content.size() - 1; y++) {
        // Original regex -> ^[0-9]{4} [0-9a-zA-Z]* {[0-9]*, [0-9]*} "[0-9a-zA-Z\/_\-\.]*"$
        if (GameStage::matchWithRegex(this->_content[y], "^[0-9]{4} [0-9a-zA-Z]* {[0-9]*, [0-9]*} \"[0-9a-zA-Z\\/_\\-\\.]*\"$")) {
            throw std::invalid_argument("Invalid line " + y);
        }
    }
    // Orignial regex -> ^XXXX "[0-9a-zA-Z\/_\-\.]*"$
    if (GameStage::matchWithRegex(this->_content[this->_content.size() - 1], "^XXXX \"[0-9a-zA-Z\\/_\\-\\.]*\"$"))
        throw std::invalid_argument("Invalid line Ended (l. " + std::to_string(this->_content.size() - 1) + ")");
}

std::vector<std::string> GameStage::readFile(const std::string &filepath) const
{
    std::string line;
    std::ifstream myfile(filepath);
    std::vector<std::string> fileContent;

    if (myfile.is_open()) {
        fileContent.clear();
        while (getline(myfile, line))
            fileContent.push_back(line);
    } else
        throw std::invalid_argument("Fail to open file: " + filepath);
    return fileContent;
}

bool GameStage::matchWithRegex(const std::string &sample, const std::string &regex)
{
    std::regex wrapper(regex);

    return std::regex_search(sample, wrapper);
}