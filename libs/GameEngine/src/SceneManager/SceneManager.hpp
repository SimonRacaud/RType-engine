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
#include <algorithm>
#include <stack>
#include "IScene.hpp"
#include "EntityManager/EntityManager.hpp"
#include "AbstractScene.hpp"
#include "env.hpp"
#include "InvalidParameterException.hpp"

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

        /**
         * @brief Creates a new scene of type from args and adds it to the scenes vector
         * 
         * @tparam SceneType Type of the Scene
         * @tparam Args Variadic template
         * @param args Arguments to be passed down to the scene
         */
        template <typename SceneType, typename... Args>
        void registerScene(Args &&...args);

        /**
         * @brief Removes a scene from the vector, and if that scene is the current scene, change it to the first scene
         * 
         * @tparam SceneType Type of scene
         */
        template <typename SceneType>
        void unregister();

        /**
         * @brief Select a scene from the vector and load it
         * 
         * @tparam SceneType Type of scene
         * @param closePrevious Bool to enable closing of previous scene
         */
        template <typename SceneType>
        void select(bool closePrevious = true);

        void flushSelection();

        /**
         * @brief Select the previous scene and load it
         * 
         */
        void selectPrevious();
        
        /**
         * @brief Checks if there is a previous scene
         * 
         * @return true 
         * @return false 
         */
        bool havePrevious() const;
        
        /**
         * @brief Get the Current scene
         * 
         * @return shared_ptr<IScene> 
         */
        shared_ptr<IScene> getCurrent();

        /**
         * @brief Gets the pointer to an abstractScene of type
         * 
         * @tparam SceneType 
         * @return shared_ptr<AbstractScene<SceneType>> 
         */
        template <class SceneType>
        shared_ptr<AbstractScene<SceneType>> get();

      private:
        vector<shared_ptr<IScene>>::iterator getSceneItFromType(const TypeIdx &type);

        shared_ptr<IScene> _currentScene{nullptr};
        shared_ptr<IScene> _nextScene{nullptr};
        vector<shared_ptr<IScene>> _scenes;
        stack<shared_ptr<IScene>> _previousScenes;
    };

    template <typename SceneType, typename... Args>
    void SceneManager::registerScene(Args &&...args)
    {
        const TypeIdx type = std::type_index(typeid(SceneType));
    
        if (getSceneItFromType(type) == _scenes.end())
            throw InvalidParameterException("This scene has already been registered");
        _scenes.push_back(std::make_shared<SceneType>(sdtd::forward<Args>(args)...));
    }
 
    template <class SceneType>
    void SceneManager::unregister()
    {
        const TypeIdx type = std::type_index(typeid(SceneType));
        auto it = getSceneItFromType(type);

        if (it == _scenes.end())
            throw InvalidParameterException("No scene with this type has been registered");
        index = std::distance(_scenes.begin(), it);
        
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