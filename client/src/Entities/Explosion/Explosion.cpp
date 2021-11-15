/*
** EPITECH PROJECT, 2021
** Explosion
** File description:
** Explosion.cpp
*/

#include "Explosion.hpp"
#include "GameCore/GameCore.hpp"

Explosion::Explosion(const vector2D &pos)
{
    std::string sound = GameCore::config->getVar<std::string>("SOUND_EXPLOSION");

    GET_EVENT_REG.registerEvent<AudioEventPlay>(sound);
    // TODO ADD ANIMATION
}