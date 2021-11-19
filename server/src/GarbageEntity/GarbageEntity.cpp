/*
** EPITECH PROJECT, 2021
** GarbageEntity
** File description:
** GarbageEntity.cpp
*/

#include "GarbageEntity.hpp"

GarbageEntity::GarbageEntity(const std::pair<size_t, size_t> &winSize, size_t xMarge, size_t yMarge) : _win(winSize), _marge(std::pair<size_t, size_t>(xMarge, yMarge))
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
    std::cout << "POSITION X === " << current.x << " : " << current.y << std::endl;
    bool outX = current.x < 0 || current.x > _win.first + _marge.first;
    bool outY = current.y < 0 || current.y > _win.second + _marge.second;

    return outX || outY;
}