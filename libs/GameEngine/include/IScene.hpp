/*
** EPITECH PROJECT , 2021
** IScene
** File description:
** \file IScene.hpp
** \author simon
** \brief
** \date 01/11/2021
*/

#ifndef ISCENE_HPP
#define ISCENE_HPP

#include "global.hpp"

namespace Engine {
    class IScene {
      public:
        virtual ~IScene() = default;

        virtual void close() = 0;
        virtual void open() = 0;

        virtual TypeIdx getType() = 0;
        virtual ClusterName getCluster() = 0;
        virtual bool isClosed() = 0;
    };
}

#endif // ISCENE_HPP
