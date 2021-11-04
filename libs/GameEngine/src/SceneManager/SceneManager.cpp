/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

#include <utility>

using namespace Engine;
 
void SceneManager::run()
{
    if (_currentScene != nullptr) {
        //TODO include gameEngine factory when merge has fixed include problems
    }
}

void SceneManager::flushSelection()
{
    if (_nextScene == nullptr)
        return;
    if (_currentScene != nullptr) {
        _currentScene->close();
        _previousScenes.push(_currentScene);
    }
    _currentScene = _nextScene;
    _currentScene->open();
    _nextScene = nullptr;
}

void SceneManager::selectPrevious()
{
    if (havePrevious()) {
        _nextScene = _previousScenes.top();
        _previousScenes.pop();        
    }
}

bool SceneManager::havePrevious() const
{
    return !_previousScenes.empty();
}

shared_ptr<IScene> SceneManager::getCurrent()
{
    return _currentScene;
}

vector<shared_ptr<IScene>>::iterator SceneManager::getSceneItFromType(const TypeIdx &type)
{
    auto it = std::find_if(_scenes.begin(), _scenes.end(), [&](shared_ptr<IScene> &sceneType) {
        return sceneType->getType() == type;
    });
    return it;
}