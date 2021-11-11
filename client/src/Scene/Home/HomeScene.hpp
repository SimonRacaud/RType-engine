/*
** EPITECH PROJECT , 2021
** HomeScene
** File description:
** \file HomeScene.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef HOMESCENE_HPP
#define HOMESCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

namespace Scene
{
    class HomeScene : public Engine::AbstractScene<HomeScene> {
      public:
        HomeScene();
        virtual ~HomeScene() = default;

        virtual void open();
    };
}

#endif // HOMESCENE_HPP
