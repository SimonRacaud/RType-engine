/*
** EPITECH PROJECT, 2021
** BulletServer
** File description:
** BulletServer.hpp
*/

#ifndef BULLETSERVER_HPP
#define BULLETSERVER_HPP

#include "Item/vector2D.hpp"

class BulletServer
{
    public:
        BulletServer(const vector2D &pos, const vector2D &velocity, const vector2D &size);
        ~BulletServer() = default;
};

#endif