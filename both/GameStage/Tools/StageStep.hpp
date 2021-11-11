/*
** EPITECH PROJECT, 2021
** StageStep
** File description:
** StageStep.hpp
*/

#ifndef STAGESTEP_HPP
#define STAGESTEP_HPP

#include "EntityType.hpp"
#include <tuple>
#include <string>

class StageStep
{
    public:
        StageStep(EntityType type, std::size_t time, std::string aiPath, std::pair<std::size_t, std::size_t> pos)
        : _type(type), _time(time), _aiPath(aiPath), _pos(pos) {};
        StageStep(const StageStep &src)
        : _type(src._type), _time(src._time), _aiPath(src._aiPath), _pos(src._pos) {};
        ~StageStep() = default;
        
        EntityType _type;
        std::size_t _time;
        std::string _aiPath;
        std::pair<std::size_t, std::size_t> _pos;
};

#endif