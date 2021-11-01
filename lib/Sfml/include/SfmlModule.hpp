/*
** PERSONAL PROJECT, 2021
** SfmlModule
** File description:
** SfmlModule.hpp
*/

#ifndef SFMLMODULE_HPP
#define SFMLMODULE_HPP

#include "FactoryObject.hpp"
#include "IGraphicalModule.hpp"
#include "FactoryObject/GetterName/GetterName.hpp"
#include "FactoryObject/GetterObject/GetterObject.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class SfmlModule: public IGraphicalModule<std::string>
{
    public:
        SfmlModule();
        ~SfmlModule();

        template <typename... buildParams> void addObject(const defaultType &type, buildParams &&... params)
        {
            this->_objectList.push_back(this->_factory.builderFactory(type, std::forward<buildParams>(params)...));
        }

        void removeObject(const std::string &);
        bool isOpen() const;
        void play();

    private:
        FactoryObject<std::string> _factory;
        std::vector<GenericObject<std::string>> _objectList;
        std::unique_ptr<sf::RenderWindow> _window;
};

#endif