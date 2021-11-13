/*
** EPITECH PROJECT , 2021
** GuiEventManager
** File description:
** \file GuiEventManager.hpp
** \author simon
** \brief
** \date 13/11/2021
*/

#ifndef GUIEVENTMANAGER_HPP
#define GUIEVENTMANAGER_HPP

#include "SetProgressBarValue.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

class GuiEventManager {
  public:
    GuiEventManager();
    virtual ~GuiEventManager() = default;

    void setProgressBarValue(const SetProgressBarValue *evt);
};

#endif // GUIEVENTMANAGER_HPP
