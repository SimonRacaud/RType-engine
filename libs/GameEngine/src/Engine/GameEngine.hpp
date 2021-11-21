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

#include <memory>
#include "ComponentManager/ComponentManager.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"
#include "IEntityManager.hpp"
#include "IGameEngine.hpp"
#include "SceneManager/SceneManager.hpp"
#include "SystemManager/SystemManager.hpp"

namespace Engine
{
    using std::unique_ptr;
    /**
     * @brief Core of the game engine
     */
    class GameEngine : public IGameEngine {
      public:
        GameEngine();
        ~GameEngine() noexcept override;

        /**
         * @brief Stop the game engine
         */
        void quit() override;
        /**
         * @brief Start the game engine
         */
        void exec() override;

        IEntityManager &getEntityManager() override;
        SystemManager &getSystemManager() override;
        ComponentManager &getComponentManager() override;
        SceneManager &getSceneManager() override;
        Event::EventCallbackRegister &getEventRegister() override;

      private:
        EntityManager *_entityManager;
        SystemManager *_systemManager;
        ComponentManager *_componentManager;
        SceneManager *_sceneManager;
        Event::EventCallbackRegister _eventRegister;
        bool _loop{true};
    };
} // namespace Engine

#endif // ENGINE_HPP