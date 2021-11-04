/*
** EPITECH PROJECT , 2021
** EngineFactory
** File description:
** \file EngineFactory.cpp
** \author simon
** \brief
** \date 02/11/2021
*/

#include "EngineFactory.hpp"
#include "Engine/GameEngine.hpp"

using namespace Engine;

unique_ptr<IGameEngine> EngineFactory::_engine = nullptr;

IGameEngine &EngineFactory::getInstance()
{
    if (EngineFactory::_engine == nullptr) {
        EngineFactory::_engine = std::make_unique<GameEngine>();
    }
    return *(EngineFactory::_engine.get());
}