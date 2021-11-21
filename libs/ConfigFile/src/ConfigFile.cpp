/*
** PERSONAL PROJECT, 2021
** ConfigFile
** File description:
** ConfigFile.cpp
*/

#include "ConfigFile.hpp"
#include <fstream>
#include <string>
#include "ConfigFileTools/ConfigFileTools.hpp"

ConfigFile::ConfigFile(const std::string &filepath, bool defaultInit)
{
    this->globalManagement(this->loadFileContent(filepath));
    if (defaultInit)
        this->initDefaultType();
}

ConfigFile::ConfigFile(const std::vector<std::string> &tab, bool defaultInit)
{
    this->globalManagement(tab);
    if (defaultInit)
        this->initDefaultType();
}

ConfigFile::~ConfigFile()
{
    this->_loadLink.clear();
    this->_fileContent.clear();
}

std::vector<std::string> ConfigFile::loadFileContent(const std::string &filepath) const
{
    std::string line;
    std::ifstream myfile(filepath);
    std::vector<std::string> fileContent;

    if (myfile.is_open()) {
        fileContent.clear();
        while (std::getline(myfile, line))
            fileContent.push_back(line);
    } else
        throw std::invalid_argument("Fail to open file: " + filepath);
    return fileContent;
}

void ConfigFile::correctInputData(std::string &line) const
{
    if (!ConfigFileTools::matchWithRegex("^[\\x00-\\x7F]+$", line) && !line.empty())
        throw std::invalid_argument("Error non ascii character");
}

void ConfigFile::commentManagement(std::string &line) const
{
    size_t tofind = line.find('#');

    if (tofind != std::string::npos)
        line = line.substr(0, tofind);
}

void ConfigFile::emptyManagement(std::string &line) const
{
    std::string::iterator next;

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

void ConfigFile::formatManagement(std::string &line) const
{
    if (!ConfigFileTools::matchWithRegex("^\"[a-zA-Z_0-9]+\": .*$", line))
        throw std::invalid_argument("Incorrect line: " + line);
}

void ConfigFile::objectInLine(char token_start, char token_end)
{
    auto next = this->_fileContent.begin();
    bool stat = false;
    size_t cnt = 0;

    for (auto it = this->_fileContent.begin(); it != this->_fileContent.end(); it++) {
        if (it->back() == token_start) {
            cnt = 1;
            do {
                next = it + 1;
                if (next == this->_fileContent.end())
                    throw std::invalid_argument(std::string("The file incorrect: token not find ") + token_end);
                if (next->back() == token_start)
                    cnt++;
                stat = next->back() == token_end;
                if (stat)
                    cnt--;
                it->append(*next);
                this->_fileContent.erase(next);
            } while (!stat || cnt != 0);
        }
    }
}

void ConfigFile::globalManagement(const std::vector<std::string> &file)
{
    std::vector<std::string> cpyFile(file);

    for (auto &line : cpyFile) {
        this->correctInputData(line);
        this->commentManagement(line);
        this->emptyManagement(line);
        if (!line.empty())
            this->_fileContent.push_back(line);
    }
    this->objectInLine('{', '}');
    this->objectInLine('[', ']');
    for (auto &line : this->_fileContent)
        this->formatManagement(line);
}

void ConfigFile::initDefaultType()
{
    this->setVarGetter<int>(ConfigFileTools::getInt);
    this->setVarGetter<bool>(ConfigFileTools::getBool);
    this->setVarGetter<float>(ConfigFileTools::getFloat);
    this->setVarGetter<double>(ConfigFileTools::getDouble);
    this->setVarGetter<std::string>(ConfigFileTools::getString);
}

std::string ConfigFile::getDataFrom(const std::string &name) const
{
    for (auto &line : this->_fileContent) {
        if (ConfigFileTools::matchWithRegex("^\"" + name + "\": .+$", line))
            return ConfigFileTools::getAfterToken(line, ": ");
    }
    throw std::invalid_argument("Unknown variable: " + name);
}

bool ConfigFile::isSetVar(const std::string &name) const
{
    for (auto &line : this->_fileContent)
        if (ConfigFileTools::matchWithRegex("^\"" + name + "\": .+$", line))
            return true;
    return false;
}

std::vector<std::string> ConfigFile::extractDataArray(const std::string &input) const
{
    std::vector<std::string> list;
    std::string rawList;
    size_t pos = 0;

    if (!ConfigFileTools::matchWithRegex("^\\[.*\\]$", input))
        throw std::invalid_argument("Incorrect line format for VECTOR: " + input);
    rawList = input.substr(1, input.length() - 2);
    while ((pos = rawList.find('\\')) != std::string::npos) {
        list.push_back(rawList.substr(0, pos));
        rawList.erase(0, pos + 1);
    }
    if (rawList.length())
        list.push_back(rawList);
    return list;
}