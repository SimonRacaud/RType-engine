/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#ifndef GAMEROOM_HPP
#define GAMEROOM_HPP

#include <thread>
#include <vector>
#include <cstddef>
#include "GameStage/GameStage.hpp"

class GameRoom
{
    public:
        GameRoom(size_t id);
        GameRoom(const GameRoom &);
        ~GameRoom();

        size_t getId() const;

        void create();
        void run();
        void destroy();

        GameRoom &operator=(const GameRoom &);

    private:
        void runStage();
        void newStage();
        void factoryStage(const StageStep &) const;

    private:
        size_t _id;
        GameStage _stage;
        std::chrono::_V2::system_clock::time_point _start;
        std::thread _thread;
};

#endif