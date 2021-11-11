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
    this->_content.clear();
}

GameStage::GameStage(std::vector<std::string> file) : _content(file)
{
    if (!this->_content.size())
        throw std::invalid_argument("Empty file content");
    this->applyFormat();
    this->checkFormat();
    this->extract();
    this->sort();
    this->_content.clear();
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
    return this->_pos >= this->_step.size();
}

StageStep GameStage::getStageStep(bool move)
{
    size_t pos = this->_pos;

    if (this->isStageEnd())
        throw std::invalid_argument("No more step");
    if (move)
        this->_pos++;
    return this->_step[pos];
}

std::queue<StageStep> GameStage::getStagePrevious(std::size_t nb) const
{
    std::queue<StageStep> queue;
    int value = this->_pos - nb;

    if (value < 0)
        value = 0;
    for (size_t i = value; i < this->_pos; i++) {
        queue.push(this->_step[i]);
    }
    return queue;
}

std::queue<StageStep> GameStage::getStageStepAt(std::size_t time, bool move)
{
    size_t i = 0;
    std::queue<StageStep> queue;

    for (i = this->_pos; i < this->_step.size() && this->_step[i]._time <= time; i++) {
        queue.push(this->_step[i]);
    }
    if (move)
        this->_pos = i;
    return queue;
}

std::string GameStage::getStageNext() const
{
    return this->_ended.nextStage;
}

void GameStage::sort()
{
    std::sort(this->_step.begin(), this->_step.end(), [](StageStep a, StageStep b) {
        return a._time > b._time;
    });
}

void GameStage::extract()
{
    this->extractHeader();
    this->extractStep();
    this->extractEnded();
}

void GameStage::extractStep()
{
    EntityType type;
    std::size_t time;
    std::string aiPath;
    std::pair<std::size_t, std::size_t> pos;
    std::vector<std::string> split;

    for (size_t y = 1; y < this->_content.size() - 1; y++) {
        split = this->splitToken(this->_content[y], ' ');
        if (split.size() != 5)
            throw std::invalid_argument("Invalid split length");
        type = this->extractEntityType(split[1]);
        aiPath = split[4].substr(1, split[4].size() - 2);
        try {
            time = std::stoi(split[0]);
            pos.first = std::stoi(split[2].substr(1, split[2].size() - 2));
            pos.second = std::stoi(split[3].substr(0, split[3].size() - 2));
        } catch (...) {
            throw std::invalid_argument("Invalid integer");
        }
        this->_step.push_back(StageStep(type, time, aiPath, pos));
    }
}

void GameStage::extractEnded()
{
    std::vector<std::string> split = this->splitToken(this->_content[this->_content.size() - 1], ' ');

    if (split.size() != 2)
        throw std::invalid_argument("Invalid split length");
    this->_ended.nextStage = split[1].substr(1, split[1].size() - 2);
}

void GameStage::extractHeader()
{
    std::vector<std::string> split = this->splitToken(this->_content[0], ' ');

    if (split.size() != 3)
        throw std::invalid_argument("Invalid split length");
    this->_header.background = split[1].substr(1, split[1].size() - 2);
    try {
        this->_header.lvl = std::stoi(split[2]);
    } catch (...) {
        throw std::invalid_argument("Invalid lvl");
    }
}

EntityType GameStage::extractEntityType(const std::string &str) const
{
    for (auto &it : this->_link) {
        if (it.first == str)
            return it.second;
    }
    throw std::invalid_argument("Invalid enum value");
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

std::vector<std::string> GameStage::splitToken(const std::string &line, char token) const
{
    std::vector<std::string> output;
    std::stringstream ss(line);
    std::string splited;

    while (std::getline(ss, splited, token))
        output.push_back(splited);
    return output;
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