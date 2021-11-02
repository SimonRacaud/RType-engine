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

#include "IGameEngine.hpp"
#include <memory>

namespace Engine
{
    using std::unique_ptr;

    class EngineFactory {
      public:
        EngineFactory() = delete;
        virtual ~EngineFactory() = delete;

        static IGameEngine &getInstance();

      private:
        static unique_ptr<IGameEngine> _engine;
    };
    unique_ptr<IGameEngine> EngineFactory::_engine = nullptr;
}

#endif // ENGINEFACTORY_HPP
