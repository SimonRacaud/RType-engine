/*
** EPITECH PROJECT , 2021
** GameRoomManager
** File description:
** GameRoomManager.hpp
*/

#include "GameRoomManager.hpp"

GameRoomManager::GameRoomManager() : _idReference(0), _rooms(), _port({0, 1})
{
    int start = ServerCore::config->getVar<int>("PORT_PAGE_START");
    int end = ServerCore::config->getVar<int>("PORT_PAGE_END");

    _port = PortManager({start, end});
}

GameRoomManager::~GameRoomManager()
{
    for (auto &it : _rooms)
        it.destroy();
    _rooms.clear();
}

void GameRoomManager::deleteRoom(GameRoom::Id id)
{
    for (size_t it = 0; it < _rooms.size(); it++) {
        if (_rooms[it].getId() == id) {
            _rooms[it].destroy();
            _rooms.erase(_rooms.begin() + it);
            return;
        }
    }
    throw std::invalid_argument("Invalid id, no room remove");
}

GameRoom::Id GameRoomManager::createRoom(GameRoom::PlayerList &list)
{
    GameRoom::Id id = _idReference;

    _idReference++;
    this->_rooms.push_back(std::move(GameRoom(list, id, GameRoom::ServerTypeTcp(_port.getPort()), GameRoom::ServerTypeUdp(_port.getPort()))));
    return id;
}