/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#ifndef GAMEROOM_HPP
#define GAMEROOM_HPP

#include <cstddef>
#include <thread>
#include <utility>
#include <vector>
#include "GameStage/GameStage.hpp"
#include "StateMachineManager/StateMachineManager.hpp"
#include "utils/timeDef.hpp"

struct EnemyRequest {
    EnemyRequest(std::string path, size_t posX, size_t posY) : path(std::move(path)), position((int) posX, (int) posY)
    {
    }

    std::string path;
    vector2D position;
};

class GameRoom {
  public:
    GameRoom(size_t id, long int start);
    GameRoom(const GameRoom &);
    ~GameRoom();

    [[nodiscard]] size_t getId() const;

    void create();
    void run();
    void destroy();
    void createEntityEnemy(uint32_t networkId);
    void destroyEntityEnemy(uint32_t networkId);

    GameRoom &operator=(const GameRoom &);

  private:
    void runStage();
    void newStage();
    void waitStart();
    void updateEnemy();
    void factoryStage(const StageStep &);

  private:
    size_t _id;
    GameStage _stage;
    long int _timeStartRun;
    size_t _enemyRefreshFreq;
    std::chrono::system_clock::time_point _start;
    StateMachineManager _stateMachine;
    std::queue<EnemyRequest> _enemyRequest;
    std::thread _thread;
    TimePoint _enemyLastRefresh;
    bool _loop{true};
};

#endif