/*
** PERSONAL PROJECT, 2021
** SfmlModule
** File description:
** SfmlModule.cpp
*/

#include "SfmlModule.hpp"

SfmlModule::SfmlModule()
{
    this->_factory.addToList(defaultType::Audio_e, GetterName::getNameAudio);
    this->_factory.addToList(defaultType::Sprite_e, GetterName::getNameSprite);
    this->_factory.addToList(defaultType::Window_e, GetterName::getNameWindow);
    this->_factory.addToList(defaultType::KeyEvent_e, GetterName::getNameKeyEvent);
    this->_factory.addToList(defaultType::Animation_e, GetterName::getNameAnimation);

    this->_factory.addToList(defaultType::Audio_e, GetterObject::getObjectAudio);
    this->_factory.addToList(defaultType::Sprite_e, GetterObject::getObjectSprite);
    this->_factory.addToList(defaultType::Window_e, GetterObject::getObjectWindow);
    this->_factory.addToList(defaultType::KeyEvent_e, GetterObject::getObjectKeyEvent);
    this->_factory.addToList(defaultType::Animation_e, GetterObject::getObjectAnimation);

    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "yolo");
    this->_window->setFramerateLimit(30);
}

SfmlModule::~SfmlModule()
{
    this->_window->close();
    this->_window.reset();
    this->_objectList.clear();
}

void SfmlModule::addObject(GenericObject<std::string> &&newMember)
{
    this->_objectList.push_back(newMember);
}

void SfmlModule::removeObject(const std::string &token)
{
    for (size_t i = 0; i < this->_objectList.size(); i++)
        if (this->_objectList[i] == token)
            this->_objectList.erase(this->_objectList.begin() + i);
}

void SfmlModule::play()
{
    for (size_t i = 0; i < this->_objectList.size(); i++)
        this->_objectList[i].run();
}