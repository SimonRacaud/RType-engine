/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

#include <utility>

using namespace Engine;

SceneManager::~SceneManager() noexcept
{
    if (this->_currentScene != nullptr) {
        this->_currentScene->close();
    }
    while (!_previousScenes.empty()) {
        shared_ptr<IScene> &scene = _previousScenes.top();
        if (!scene->isClosed()) {
            scene->close();
        }
        _previousScenes.pop();
    }
}

void SceneManager::run()
{
    TimePoint now = Clock::now();

    if (_currentScene != nullptr) {
        EngineFactory::getInstance().getSystemManager().executeCycle();
    }
    if ((now - _previousSceneFlush) > SCENE_MANAG_FREQ_FLUSH_CHANGE) {
        _previousSceneFlush = now;
        this->flushSelection();
    }
}

void SceneManager::flushSelection()
{
    if (_nextScene == nullptr)
        return;
    if (_currentScene != nullptr) {
        if (_closeSceneOnChange) {
            SHOW_DEBUG("Scene: close scene type=" + TYPE_STR(_currentScene->getType()));
            _currentScene->close();
        }
        _previousScenes.push(_currentScene);
    }
    _currentScene = _nextScene;
    SHOW_DEBUG("Scene: open scene type=" + TYPE_STR(_currentScene->getType()));
    if (_currentScene->isClosed()) {
        _currentScene->open();
    }
    _nextScene = nullptr;
}

void SceneManager::selectPrevious()
{
    if (this->havePrevious()) {
        _nextScene = _previousScenes.top();
        _closeSceneOnChange = true;
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
    auto it = std::find_if(_scenes.begin(), _scenes.end(), [&](const shared_ptr<IScene> &scene) {
        return scene->getType().hash_code() == type.hash_code();
    });
    return it;
}