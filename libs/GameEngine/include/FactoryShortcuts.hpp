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

#include "SystemManager/SystemManager.hpp"
namespace Engine {
    #define GET_SYS_M    Engine::EngineFactory::getInstance().getSystemManager()
    #define GET_EVENT_REG Engine::EngineFactory::getInstance().getEventRegister()

}

#endif // FACTORYSHORTCUTS_HPP
