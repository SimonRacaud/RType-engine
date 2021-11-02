/*
** EPITECH PROJECT , 2021
** FactoryShortcuts
** File description:
** \file FactoryShortcuts.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef FACTORYSHORTCUTS_HPP
#define FACTORYSHORTCUTS_HPP

#include "EngineFactory.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace Engine {
    #define GET_ENTITY_M EngineFactory::getInstance().getEntityManager()
    #define GET_SYS_M    EngineFactory::getInstance().getSystemManager()
}

#endif // FACTORYSHORTCUTS_HPP
