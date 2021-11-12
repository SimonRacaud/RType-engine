/*
** EPITECH PROJECT , 2021
** ScoreComponent
** File description:
** \file ScoreComponent.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Engine {
    struct ScoreComponent : public BaseComponent<ScoreComponent> {
      public:
        ScoreComponent() = default;
        virtual ~ScoreComponent() = default;

        size_t value{0};
    };
}

#endif // SCORECOMPONENT_HPP
