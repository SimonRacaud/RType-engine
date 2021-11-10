/*
** EPITECH PROJECT , 2021
** DebugScene
** File description:
** \file DebugScene.hpp
** \author simon
** \brief
** \date 08/11/2021
*/

#ifndef DEBUGSCENE_HPP
#define DEBUGSCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"

namespace Scene
{
    class DebugScene : public Engine::AbstractScene<DebugScene> {
      public:
        DebugScene();
        virtual ~DebugScene() = default;

        virtual void open();
    };
}

#endif // DEBUGSCENE_HPP
