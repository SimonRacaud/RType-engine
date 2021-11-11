/*
** EPITECH PROJECT , 2021
** SizeComponent
** File description:
** \file SizeComponent.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef SIZECOMPONENT_HPP
#define SIZECOMPONENT_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Engine {
    struct SizeComponent : public BaseComponent<SizeComponent> {
        SizeComponent(size_t w, size_t h) : width(w), height(h) {};
        virtual ~SizeComponent() = default;

        size_t width{0};
        size_t height{0};
    };
}

#endif // SIZECOMPONENT_HPP
