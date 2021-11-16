/*
** EPITECH PROJECT , 2021
** SettingsScene
** File description:
** \file SettingsScene.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef SETTINGSSCENE_HPP
#define SETTINGSSCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

namespace Scene
{
    class SettingsScene : public Engine::AbstractScene<SettingsScene> {
      public:
        SettingsScene();
        virtual ~SettingsScene() = default;

        virtual void open();

      private:
        std::string _audio;
    };
}

#endif // SETTINGSSCENE_HPP
