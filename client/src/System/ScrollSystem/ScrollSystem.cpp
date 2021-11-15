/*
** EPITECH PROJECT , 2021
** ScrollSystem
** File description:
** \file ScrollSystem.cpp
** \author simon
** \brief
** \date 11/11/2021
*/

#include "ScrollSystem.hpp"
#include "Component/Scroll.hpp"

using namespace System;
using namespace Engine;

static const Engine::Time freq = static_cast<Engine::Time>(100);

ScrollSystem::ScrollSystem()
    : Engine::AbstractSystem<ScrollSystem>(freq, SystemPriority::LOW)
{
    this->setRequirements<Engine::Position, Component::Scroll>();
}

void ScrollSystem::run(const vector<Engine::Entity> &entities)
{
    for (const Engine::Entity entity : entities) {
        auto [position, scroll] = GET_COMP_M.getList<Engine::Position, Component::Scroll>(entity);

        if (position.x <= -(scroll.width / 2)) {
            position.x = 0;
        }
    }
}