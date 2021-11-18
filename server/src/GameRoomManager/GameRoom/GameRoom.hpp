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
#include "StateMachineManager/StateMachineManager.hpp"

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
        void createEntityEnemy(uint32_t networkId);
        void destroyEntityEnemy(uint32_t networkId);

        GameRoom &operator=(const GameRoom &);

    private:
        void runStage();
        void newStage();
        void updateEnemy();
        void factoryStage(const StageStep &) const;

    private:
        size_t _id;
        GameStage _stage;
        std::chrono::system_clock::time_point _start;
        StateMachineManager _stateMachine;
        std::queue<std::string> _enemyRequest;
        std::thread _thread;
};

#endif