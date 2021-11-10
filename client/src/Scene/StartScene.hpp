/*
** EPITECH PROJECT , 2021
** StartScene
** File description:
** \file StartScene.hpp
** \author simon
** \brief
** \date 04/11/2021
*/

#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "Events/TimerEvent.hpp"

namespace Scene
{
    class StartScene : public Engine::AbstractScene<StartScene>
    {
      public:
        StartScene();
        virtual ~StartScene() = default;

        virtual void open();

        static void timerCallback(const TimerEvent *e);
    };
}

#endif // STARTSCENE_HPP
