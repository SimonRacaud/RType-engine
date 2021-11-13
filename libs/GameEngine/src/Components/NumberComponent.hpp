/*
** EPITECH PROJECT , 2021
** NumberComponent
** File description:
** \file NumberComponent.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef NUMBERCOMPONENT_HPP
#define NUMBERCOMPONENT_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Engine {
    struct NumberComponent : public BaseComponent<NumberComponent> {
        NumberComponent(size_t value): value(value) {};
        NumberComponent() = default;
        virtual ~NumberComponent() = default;

        size_t value;
    };
}

#endif // NUMBERCOMPONENT_HPP
