/*
** EPITECH PROJECT , 2021
** EngineFactory
** File description:
** \file EngineFactory.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef ENGINEFACTORY_HPP
#define ENGINEFACTORY_HPP

#include "Engine/GameEngine.hpp"

namespace Engine
{
    class EngineFactory {
      public:
        EngineFactory() = delete;
        virtual ~EngineFactory() = delete;

        static GameEngine &getInstance();

      private:
        static GameEngine _engine;
    };

    GameEngine EngineFactory::_engine = GameEngine();
}

#endif // ENGINEFACTORY_HPP
