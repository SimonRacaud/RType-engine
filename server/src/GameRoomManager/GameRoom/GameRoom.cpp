/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#include "GameRoom.hpp"
#include "ServerCore/ServerCore.hpp"

GameRoom::GameRoom(size_t id) : _id(id), _stage(ServerCore::config->getVar<std::string>("FIRST_STAGE")), _start(std::chrono::system_clock::now())
{
}

GameRoom::GameRoom(const GameRoom &src) : _id(src._id), _stage(src._stage), _start(src._start)
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
        this->runStage();
        // TODO CALL UPDATE ENEMY ACTION (POL'S METHODE)
        // TODO SERVER SYNC
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
    this->_start = src._start;
    return *this;
}

void GameRoom::runStage()
{
    std::chrono::duration<double> tmp = std::chrono::system_clock::now() - this->_start;
    size_t nb_sec = tmp.count();
    std::queue<StageStep> queue = this->_stage.getStageStepAt(nb_sec);

    while (queue.size()) {
        this->factoryStage(queue.front());
        queue.pop();
    }
    if (this->_stage.isStageEnd())
        this->newStage();
}

void GameRoom::newStage()
{
    if (!this->_stage.isStageEnd())
        throw std::invalid_argument("Stage not ended");
    this->_stage = GameStage(this->_stage.getStageNext());
    this->_start = std::chrono::system_clock::now();
}

void GameRoom::factoryStage(const StageStep &step) const
{
    switch (step._type)
    {
        case EntityType::ENEMY:
        {
            // TODO CALL POL CREATE ENEMY
            std::pair<int, int> velocityEnemy = ServerCore::config->getVar<std::pair<int, int>>("ENEMY_DEFAULT_VELOCITY");
            ServerCore::network->createEntity(_id, "ENEMY", netVector2f(step._pos.first, step._pos.second), netVector2f(velocityEnemy.first, velocityEnemy.second));
        }
            break;
        case EntityType::EQUIPMENT:
        {
            std::pair<int, int> velocityEquipment = ServerCore::config->getVar<std::pair<int, int>>("EQUIPMENT_DEFAULT_VELOCITY");
            ServerCore::network->createEntity(_id, "EQUIPMENT", netVector2f(step._pos.first, step._pos.second), netVector2f(velocityEquipment.first, velocityEquipment.second));
        }
            break;
        default:
            throw std::invalid_argument("Invalid EntityType -> None register");
            break;
    }
}