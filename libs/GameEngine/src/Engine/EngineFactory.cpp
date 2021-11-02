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

using namespace Engine;

GameEngine &EngineFactory::getInstance()
{
    return EngineFactory::_engine;
}