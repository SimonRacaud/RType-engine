/*
** EPITECH PROJECT , 2021
** GameScene
** File description:
** \file GameScene.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

namespace Scene
{
    class GameScene : public Engine::AbstractScene<GameScene> {
      public:
        GameScene();
        virtual ~GameScene() = default;

        virtual void open();
        void initGame() const;

      private:
        std::string _audio;
    };
}

#endif // GAMESCENE_HPP
