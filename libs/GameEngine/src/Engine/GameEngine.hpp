/*
** EPITECH PROJECT , 2021
** Engine
** File description:
** \file Engine.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "EntityManager/EntityManager.hpp"
#include "SystemManager/SystemManager.hpp"
#include "ComponentManager/ComponentManager.hpp"
#include "SceneManager/SceneManager.hpp"

namespace Engine
{
    class GameEngine {
      public:
        GameEngine() = default;
        virtual ~GameEngine() = default;

        void quit();
        void exec();

        EntityManager &getEntityManager();
        SystemManager &getSystemManager();
        ComponentManager &getComponentManager();
        SceneManager &getSceneManager();
        // EventCallbackRegister &getEventRegister(); TODO

      private:
        // EventCallbackRegister _eventRegister; TODO
        EntityManager _entityManager;
        SystemManager _systemManager;
        ComponentManager _componentManager;
        SceneManager _sceneManager;
        bool _loop{true};
    };
}

#endif // ENGINE_HPP
