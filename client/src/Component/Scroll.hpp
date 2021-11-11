/*
** EPITECH PROJECT , 2021
** Scroll
** File description:
** \file Scroll.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef SCROLL_HPP
#define SCROLL_HPP

#include "EngineCore.hpp"

namespace Component {
    struct Scroll : public Engine::BaseComponent<Scroll> {
        Scroll(float maxPosition): maxPosition(maxPosition) {};
        Scroll() = default;
        virtual ~Scroll() = default;

        float maxPosition{0};
    };
}

#endif // SCROLL_HPP
