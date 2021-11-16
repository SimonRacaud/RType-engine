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
#include "Components/Position.hpp"
#include "include/Tram/ComponentSync.hpp"
#include "include/Tram/DestroyEntity.hpp"

class GarbageEntity
{
    public:
        GarbageEntity(const std::pair<size_t, size_t> &);
        ~GarbageEntity();

        std::vector<Tram::DestroyEntity> processing(const std::vector<Tram::ComponentSync> &);

    private:
        bool isOutOfRange(Engine::Position) const;

    private:
        std::pair<size_t, size_t> _win;
};

#endif