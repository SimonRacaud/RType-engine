/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#include "GameRoom.hpp"

GameRoom::GameRoom(PlayerList &player, Id id, ServerTypeTcp tcp, ServerTypeUdp udp) : _id(id), _playerList(player), _tcp(std::move(tcp)), _udp(std::move(udp))
{
    // TODO START SERVER TCP && UDP
}

GameRoom::GameRoom(const GameRoom &src) : _id(src._id), _playerList(src._playerList), _tcp(std::move(src._tcp)), _udp(std::move(src._udp))
{
}

GameRoom::~GameRoom()
{
    this->destroy();
    // TODO CLOSE SERVER TCP && UDP
}

GameRoom::Id GameRoom::getId() const
{
    return _id;
}

// TODO IF create don't work try something like this
// void run2(GameRoom *src) {
//     src->run();
// }
//
// void GameRoom::create()
// {
//     this->_thread = std::thread(run2, this);
// }

void GameRoom::create()
{
    this->_thread = std::thread(&GameRoom::run, this);
}

void GameRoom::run()
{
    bool loop = true;

    this->waitConnection();
    while (loop) {
        // TODO RUN GAME && SERVER
    }
}

void GameRoom::destroy()
{
    if (this->_thread.joinable())
        this->_thread.join();
}

void GameRoom::waitConnection()
{
    for (auto &it : this->_playerList) {
        // TODO ACCEPT USER CONECTION (UDP - TCP)
    }
}

GameRoom &GameRoom::operator=(const GameRoom &src)
{
    this->_id = src._id;
    this->_playerList = src._playerList;
    this->_udp = std::move(src._udp);
    this->_tcp = std::move(src._tcp);
    return *this;
}