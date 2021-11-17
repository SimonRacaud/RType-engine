/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#include "GameRoom.hpp"
#include "ServerCore/ServerCore.hpp"

GameRoom::GameRoom(size_t id) : _id(id), _stage(ServerCore::config->getVar<std::string>("FIRST_STAGE"))
{
}

GameRoom::GameRoom(const GameRoom &src) : _id(src._id), _stage(src._stage)
{
}

GameRoom::~GameRoom()
{
    this->destroy();
}

size_t GameRoom::getId() const
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

    while (loop) {
        // TODO RUN GAME STAGE
    }
}

void GameRoom::destroy()
{
    if (this->_thread.joinable())
        this->_thread.join();
}

GameRoom &GameRoom::operator=(const GameRoom &src)
{
    this->_id = src._id;
    this->_stage = src._stage;
    return *this;
}