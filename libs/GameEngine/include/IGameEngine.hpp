/*
** EPITECH PROJECT , 2021
** IGameEngine
** File description:
** \file IGameEngine.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef IGAMEENGINE_HPP
#define IGAMEENGINE_HPP

#include "IEntityManager.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

namespace Engine
{
    class ComponentManager;
    class SystemManager;
    class SceneManager;

    class IGameEngine {
      public:
        virtual ~IGameEngine() = default;

        virtual void quit() = 0;
        virtual void exec() = 0;

        virtual IEntityManager &getEntityManager() = 0;
        virtual SystemManager &getSystemManager() = 0;
        virtual ComponentManager &getComponentManager() = 0;
        virtual SceneManager &getSceneManager() = 0;
        virtual Event::EventCallbackRegister &getEventRegister() = 0;
    };
}

#endif // IGAMEENGINE_HPP
