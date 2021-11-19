/*
** EPITECH PROJECT , 2021
** GameRoomManager
** File description:
** GameRoomManager.hpp
*/

#include "GameRoomManager.hpp"

GameRoomManager::GameRoomManager() : _rooms()
{
}

GameRoomManager::~GameRoomManager()
{
    for (auto &it : _rooms)
        it->destroy();
    _rooms.clear();
}

void GameRoomManager::deleteRoom(size_t roomId)
{
    for (size_t it = 0; it < _rooms.size(); it++) {
        if (_rooms[it]->getId() == roomId) {
            _rooms[it]->destroy();
            _rooms.erase(_rooms.begin() + it);
            return;
        }
    }
    throw std::invalid_argument("Invalid id, no room remove");
}

void GameRoomManager::createRoom(size_t roomId)
{
    this->_rooms.push_back(make_unique<GameRoom>(roomId));
    this->_rooms.back()->create();
}

void GameRoomManager::createEntityEnemy(size_t roomId, uint32_t networkId)
{
    for (size_t it = 0; it < _rooms.size(); it++) {
        if (_rooms[it]->getId() == roomId) {
            _rooms[it]->createEntityEnemy(networkId);
            return;
        }
    }
    throw std::invalid_argument("Invalid id, no room found, no enemy created");
}

void GameRoomManager::destroyEntityEnemy(size_t roomId, uint32_t networkId)
{
    for (size_t it = 0; it < _rooms.size(); it++) {
        if (_rooms[it]->getId() == roomId) {
            _rooms[it]->destroyEntityEnemy(networkId);
            return;
        }
    }
    throw std::invalid_argument("Invalid id, no room found, no enemy destroyed");
}