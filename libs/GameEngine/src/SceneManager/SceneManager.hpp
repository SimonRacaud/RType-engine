/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>
#include "AbstractScene/AbstractScene.hpp"
#include "Engine/EngineFactory.hpp"
#include "EntityManager/EntityManager.hpp"
#include "Exception/InvalidParameterException.hpp"
#include "Exception/NotRegisteredException.hpp"
#include "IScene.hpp"
#include "env.hpp"

namespace Engine
{
    using std::shared_ptr;
    using std::stack;
    using std::vector;

    class SceneManager {
      public:
        SceneManager() = default;
        virtual ~SceneManager();

        void run();

        /**
         * @brief Creates a new scene of type from args and adds it to the
         * scenes vector
         *
         * @tparam SceneType Type of the Scene
         * @tparam Args Variadic template
         * @param args Arguments to be passed down to the scene
         */
        template <typename SceneType, typename... Args>
        void registerScene(Args &&...args);

        /**
         * @brief Removes a scene from the vector, and if that scene is the
         * current scene, change it to the first scene
         * @deprecated
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

        void select(const shared_ptr<IScene> &scene, bool closePrevious = true);

        template <class SceneType> bool isCurrent() const;

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
        /**
         * @brief Flush selection changes the current into the next and closes
         * current
         */
        void flushSelection();

        template <class SceneType>
        void _checkType() const;

      private:
        vector<shared_ptr<IScene>>::iterator getSceneItFromType(const TypeIdx &type);

        shared_ptr<IScene> _currentScene{nullptr};
        shared_ptr<IScene> _nextScene{nullptr};
        bool _closeSceneOnChange{true};
        vector<shared_ptr<IScene>> _scenes;
        stack<shared_ptr<IScene>> _previousScenes;
        TimePoint _previousSceneFlush;
    };

    template <typename SceneType, typename... Args>
    void SceneManager::registerScene(Args &&...args)
    {
        this->_checkType<SceneType>();

        const TypeIdx type = AbstractScene<SceneType>::type;

        if (getSceneItFromType(type) != _scenes.end())
            throw FatalErrorException(
                "This scene has already been registered");
        _scenes.push_back(
            std::make_shared<SceneType>(std::forward<Args>(args)...));
    }

    template <class SceneType> void SceneManager::unregister()
    {
        throw FatalErrorException(
            "SceneManager::unregister Deprecated method");
        auto it = getSceneItFromType(AbstractScene<SceneType>::type);

        if (it == _scenes.end()) {
            throw NotRegisteredException(
                "No scene with this type has been registered");
        }
        if (_currentScene != nullptr
            && _currentScene->getType().hash_code()
                == (*it)->getType().hash_code()) {
            throw InvalidParameterException(
                "Trying to unregister current loaded scene");
        }
        if (_scenes.size() > 1) {
            (*it) = _scenes.back();
        }
        _scenes.pop_back();
    }

    template <typename SceneType> void SceneManager::select(bool closePrevious)
    {
        this->_checkType<SceneType>();

        auto it = getSceneItFromType(AbstractScene<SceneType>::type);

        if (it == _scenes.end())
            throw NotRegisteredException(
                "Could not select scene that has not been registered");
        _nextScene = *it;
        this->_closeSceneOnChange = closePrevious;
    }

    template <class SceneType>
    shared_ptr<AbstractScene<SceneType>> SceneManager::get()
    {
        this->_checkType<SceneType>();

        const TypeIdx type = AbstractScene<SceneType>::type;
        auto it = getSceneItFromType(type);

        if (it == _scenes.end())
            throw InvalidParameterException(
                "Could not get pointer to non existing scene");
        return reinterpret_cast<AbstractScene<SceneType>>(*it);
    }

    template <class SceneType> bool SceneManager::isCurrent() const
    {
        this->_checkType<SceneType>();
         return !(_currentScene == nullptr)
            && _currentScene->getType().hash_code()
            == SceneType::type.hash_code();
    }

    template <class SceneType> void SceneManager::_checkType() const
    {
        static_assert(
            std::is_base_of<AbstractScene<SceneType>, SceneType>::value,
            "Invalid scene type");
    }

} // namespace Engine

#endif /* !SCENEMANAGER_HPP_ */