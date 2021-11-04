/*
** EPITECH PROJECT , 2021
** Engine
** File description:
** \file Engine.cpp
** \author simon
** \brief
** \date 02/11/2021
*/

#include "GameEngine.hpp"

using namespace Engine;

void GameEngine::quit()
{
    this->_loop = false;
}

void GameEngine::exec()
{
    while (_loop) {
        this->_sceneManager.run();
        this->_sceneManager.flushSelection();
    }
}

ComponentManager &GameEngine::getComponentManager()
{
    return _componentManager;
}

IEntityManager &GameEngine::getEntityManager()
{
    return _entityManager;
}

SystemManager &GameEngine::getSystemManager()
{
    return _systemManager;
}

SceneManager &GameEngine::getSceneManager()
{
    return _sceneManager;
}

Event::EventCallbackRegister &GameEngine::getEventRegister()
{
    return _eventRegister;
}