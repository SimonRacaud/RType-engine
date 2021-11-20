/*
** EPITECH PROJECT , 2021
** PhysicController
** File description:
** \file PhysicController.hpp
** \author simon
** \brief
** \date 20/11/2021
*/

#ifndef PHYSICCONTROLLER_HPP
#define PHYSICCONTROLLER_HPP

#include "Components/Velocity.hpp"
#include "Components/Position.hpp"
#include "utils/timeDef.hpp"

class PhysicController {
  public:
    PhysicController() = delete;
    virtual ~PhysicController() = delete;

    static void Update(Engine::Velocity const &velocity,
        Engine::Position &position, TimePoint &lastUpdate);
};

#endif // PHYSICCONTROLLER_HPP
