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

void GarbageEntity::processing(const Tram::ComponentSync &tram, IServerNetworkCore &networkCore)
{
    if (this->isOutOfRange(*(static_cast<Engine::Position *>(tram.component)))) {
        networkCore.destroyEntity(tram.roomId, tram.networkId);
    }
}

bool GarbageEntity::isOutOfRange(Engine::Position current) const
{
    bool outX = current.x < 0 || current.x > _win.first;
    bool outY = current.y < 0 || current.y > _win.second;

    return outX || outY;
}