/*
** EPITECH PROJECT , 2021
** RoomListScene
** File description:
** \file RoomListScene.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef ROOMLISTSCENE_HPP
#define ROOMLISTSCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

namespace Scene
{
    class RoomListScene : public Engine::AbstractScene<RoomListScene> {
      public:
        RoomListScene();
        virtual ~RoomListScene() = default;

        virtual void open();

        virtual void close() override;

      private:
        void reloadRoomList(std::vector<size_t> const &roomIdList);
    };
}

#endif // ROOMLISTSCENE_HPP
