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

        /**
         * @brief Singleton of the Game Engine core
         * @return
         */
        static IGameEngine &getInstance();

      private:
        static unique_ptr<IGameEngine> _engine;
    };
}

#endif // ENGINEFACTORY_HPP
