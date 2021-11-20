/*
** EPITECH PROJECT , 2021
** PhysicController
** File description:
** \file PhysicController.cpp
** \author simon
** \brief
** \date 20/11/2021
*/

#include "PhysicController.hpp"

void PhysicController::Update(Engine::Velocity const &velocity,
    Engine::Position &position, TimePoint &lastUpdate)
{
    TimePoint now = steadyClock::now();
    if (lastUpdate.time_since_epoch().count() == 0) {
        lastUpdate = now;
    }
    float delta = (float)DURATION_CAST(steadyClock::now() - lastUpdate).count() / 1000;

    position.x += velocity.x * delta;
    position.y += velocity.y * delta;
    lastUpdate = now;
}