/*
** EPITECH PROJECT , 2021
** SelectPreviousScene
** File description:
** \file SelectPreviousScene.hpp
** \author simon
** \brief
** \date 13/11/2021
*/

#ifndef SELECTPREVIOUSSCENE_HPP
#define SELECTPREVIOUSSCENE_HPP

#include "Event/IEvent.hpp"

class SelectPreviousScene : public Engine::Event::IEvent
{
  public:
    SelectPreviousScene() {}
    virtual ~SelectPreviousScene() = default;

    std::type_index getType() const override {
        return std::type_index(typeid(this));
    }
};

#endif // SELECTPREVIOUSSCENE_HPP
