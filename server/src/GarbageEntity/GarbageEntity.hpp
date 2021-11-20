/*
** EPITECH PROJECT, 2021
** GarbageEntity
** File description:
** GarbageEntity.hpp
*/

#ifndef GARBAGEENTITY_HPP
#define GARBAGEENTITY_HPP

#include <tuple>
#include <vector>
#include "IServerNetworkCore.hpp"
#include "Components/Position.hpp"
#include "Tram/ComponentSync.hpp"
#include "Tram/DestroyEntity.hpp"

class GarbageEntity
{
    public:
        GarbageEntity(const std::pair<size_t, size_t> &windowSize, size_t xMarge = 0, size_t yMarge = 0);
        ~GarbageEntity();

        void processing(const Tram::ComponentSync &tram, IServerNetworkCore &networkCore);

    private:
        bool isOutOfRange(Engine::Position const&) const;

    private:
        std::pair<size_t, size_t> _win;
        std::pair<size_t, size_t> _marge;
};

#endif