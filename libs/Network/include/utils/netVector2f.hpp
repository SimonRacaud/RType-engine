/*
** EPITECH PROJECT , 2021
** vector2f
** File description:
** \file vector2f.hpp
** \author simon
** \brief
** \date 17/11/2021
*/

#ifndef NET_VECTOR2F_HPP
#define NET_VECTOR2F_HPP

namespace Network {
    struct netVector2f {
        netVector2f() = default;
        netVector2f(netVector2f const& other) : x(other.x), y(other.y) {};
        netVector2f(float x, float y) : x(x), y(y) {}

        void operator=(netVector2f const& other) {
            x = other.x;
            y = other.y;
        }

        float x{0};
        float y{0};
    };
}

#endif // VECTOR2F_HPP
