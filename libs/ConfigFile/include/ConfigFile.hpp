/*
** PERSONAL PROJECT, 2021
** ConfigFile
** File description:
** ConfigFile.hpp
*/

#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <any>
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>

class ConfigFile {
  public:
    ConfigFile(const std::string &filepath, bool defaultInit = true);
    ConfigFile(const std::vector<std::string> &tab, bool defaultInit = true);
    ~ConfigFile();

    [[nodiscard]] bool isSetVar(const std::string &name) const;
    template <typename varType> [[nodiscard]] varType getVar(const std::string &name) const
    {
      std::size_t key = typeid(varType).hash_code();
      auto it = this->_loadLink.find(key);

      if (it != this->_loadLink.end()) {
        try {
          return std::any_cast<varType>(this->_loadLink.at(key)(this->getDataFrom(name)));
        } catch (const std::bad_any_cast &e) {
            (void) e;
            throw std::invalid_argument("Invalide function to load: " + std::string(typeid(varType).name()));
        }
      } else
        throw std::invalid_argument("No getter for: " + std::string(typeid(varType).name()));
    }

    template <typename varType> [[nodiscard]] std::vector<varType> getVectorOf(const std::string &name) const
    {
      std::vector<varType> list;
      std::size_t key = typeid(varType).hash_code();
      auto it = this->_loadLink.find(key);

      if (it != this->_loadLink.end()) {
        try {
          std::vector<std::string> extractedList = this->extractDataArray(this->getDataFrom(name));

          for (auto &str : extractedList)
            list.push_back(std::any_cast<varType>(this->_loadLink.at(key)(str)));
          return list;
        } catch (const std::bad_any_cast) {
          throw std::invalid_argument("Invalide function to load: " + std::string(typeid(varType).name()));
        }
      } else
        throw std::invalid_argument("No getter for: " + std::string(typeid(varType).name()));
    }

    template <typename varType> void setVarGetter(std::function<std::any (const std::string &)> func, bool force = false)
    {
      std::size_t key = typeid(varType).hash_code();
      auto it = this->_loadLink.find(key);

      if (it != this->_loadLink.end() && !force)
        throw std::invalid_argument("Getter already exist for: " + std::string(typeid(varType).name()));
      this->_loadLink[key] = func;
    }

  private:
    // GENERIC
    [[nodiscard]] std::vector<std::string> loadFileContent(const std::string &filepath) const;

    // INTERNAL
    void emptyManagement(std::string &line) const;
    void formatManagement(std::string &line) const;
    void correctInputData(std::string &line) const;
    void commentManagement(std::string &line) const;
    void objectInLine(char token_start, char token_end);
    void globalManagement(const std::vector<std::string> &file);

    // DEFAULT
    void initDefaultType();

    // PARSING
    [[nodiscard]] std::string getDataFrom(const std::string &name) const;
    [[nodiscard]] std::vector<std::string> extractDataArray(const std::string &input) const;

  private:
    std::vector<std::string> _fileContent;
    std::unordered_map<std::size_t, std::function<std::any (const std::string &)>> _loadLink;
};

#endif