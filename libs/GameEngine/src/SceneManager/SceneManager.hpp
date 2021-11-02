/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <vector>
#include <memory>
#include <stack>
#include "IScene.hpp"
#include "EntityManager/EntityManager.hpp"
#include "AbstractScene.hpp"
#include "env.hpp"

namespace Engine
{
    using std::shared_ptr;
    using std::vector;
    using std::stack;

    class SceneManager {
      public:
        SceneManager() = default;
        ~SceneManager() = default;

        void run();

        template <typename SceneType, typename... Args>
        void registerScene(Args &&...args);

        template <typename SceneType>
        void unregister();

        template <typename SceneType>
        void select(bool closePrevious = true);
        void flushSelection();

        void selectPrevious();
        bool havePrevious() const;

        shared_ptr<IScene> getCurrent();

        template <class SceneType>
        shared_ptr<AbstractScene<SceneType>> get();

      private:
        shared_ptr<IScene> _currentScene{nullptr};
        shared_ptr<IScene> _nextScene{nullptr};
        vector<shared_ptr<IScene>> _scenes;
        stack<shared_ptr<IScene>> _previousScenes;
    };

    template <typename SceneType, typename... Args>
    void SceneManager::registerScene(Args &&...args)
    {
        // TODO
//        const std::type_info &type = typeid(SceneType);
//
//        if (std::find_if(_types.begin(),
//                _types.end(),
//                [&type](auto &sceneType) {
//                    return sceneType.get() == type;
//                })
//            != _types.end()) {
//            throw std::exception();
//        }
//        _scenes.push_back(std::make_shared<SceneType>(std::forward<Args>(args)...));
//        _types.emplace_back(typeid(SceneType));
    }


    template <class SceneType>
    void SceneManager::unregister()
    {
        // TODO
//        std::size_t index = 0;
//        const std::type_info &type = typeid(T);
//        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
//            return sceneType.get() == type;
//        });
//
//        if (type_it == _types.end()) {
//            throw std::exception();
//        }
//        index = std::distance(_types.begin(), type_it);
//        if (_currentScene == _scenes[index]) {
//            this->setCurrentScene((!_scenes.empty()) ? _scenes.front() : nullptr);
//        }
//        _types[index] = _types.back();
//        _types.pop_back();
//        _scenes[index] = _scenes.back();
//        _scenes.pop_back();
    }


    template <typename SceneType>
    void SceneManager::select(bool closePrevious)
    {
        // TODO
//        std::size_t index = 0;
//        const std::type_info &type = typeid(T);
//        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
//            return sceneType.get() == type;
//        });
//        if (type_it == _types.end()) {
//            throw std::exception();
//        }
//        _toClose = close;
//        _toOpen = open;
//        index = std::distance(_types.begin(), type_it);
//        if (_currentScene == nullptr) {
//            this->setCurrentScene(_scenes[index]);
//        } else {
//            _nextScene = _scenes[index];
//        }
    }


    template <class SceneType>
    shared_ptr<AbstractScene<SceneType>> SceneManager::get()
    {
        // TODO
//        std::size_t index = 0;
//        const std::type_info &type = typeid(T);
//        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
//            return sceneType.get() == type;
//        });
//
//        if (type_it == _types.end()) {
//            throw std::exception();
//        }
//        index = std::distance(_types.begin(), type_it);
//        return _scenes[index];
    }

} // namespace Engine

#endif /* !SCENEMANAGER_HPP_ */