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

#include "IEntityManager.hpp"
#include "SystemManager/SystemManager.hpp"
#include "ComponentManager/ComponentManager.hpp"
#include "SceneManager/SceneManager.hpp"
#include "IGameEngine.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

namespace Engine
{
    /**
     * @brief Core of the game engine
     */
    class GameEngine : public IGameEngine {
      public:
        GameEngine() = default;
        virtual ~GameEngine() = default;

        /**
         * @brief Stop the game engine
         */
        void quit();
        /**
         * @brief Start the game engine
         */
        void exec();

        IEntityManager &getEntityManager();
        SystemManager &getSystemManager();
        ComponentManager &getComponentManager();
        SceneManager &getSceneManager();
        Event::EventCallbackRegister &getEventRegister();

      private:
        Event::EventCallbackRegister _eventRegister;
        EntityManager _entityManager;
        SystemManager _systemManager;
        ComponentManager _componentManager;
        SceneManager _sceneManager;
        bool _loop{true};
    };
}

#endif // ENGINE_HPP
