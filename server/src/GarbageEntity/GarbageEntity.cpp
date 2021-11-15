/*
** EPITECH PROJECT, 2021
** GarbageEntity
** File description:
** GarbageEntity.cpp
*/

#include "GarbageEntity.hpp"

GarbageEntity::GarbageEntity(const std::pair<size_t, size_t> &winSize) : _win(winSize)
{
}

GarbageEntity::~GarbageEntity()
{
}

std::vector<Tram::DestroyEntity> GarbageEntity::processing(const std:vector<Tram::ComponentSync> &src)
{
    std::vector<Tram::DestroyEntity> output;

    this->_list.clear();
    for (auto &it : src) {
        if (this->isOutOfRange(*(static_cast<Engine::Position *>(it.component)))) {
            output.push_back(Tram::DestroyEntity(src.roomId, src.NetworkId));
        }
    }
    this->_list.clear();
    return output;
}

bool GarbageEntity::isOutOfRange(Engine::Position current) const
{
    bool outX = current.x < 0 || current.x > _win.first;
    bool outY = current.y < 0 || current.y > _win.second;

    return outX || outY;
}