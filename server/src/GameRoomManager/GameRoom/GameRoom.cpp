/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#include "GameRoom.hpp"
#include "ServerCore/ServerCore.hpp"

GameRoom::GameRoom(size_t id, long int start) :
      _id(id),
      _stage(ServerCore::config->getVar<std::string>("FIRST_STAGE")),
      _timeStartRun(start),
      _enemyRefreshFreq((size_t)ServerCore::config->getVar<int>("ENEMY_REFRESH_RATE")),
      _start(std::chrono::system_clock::now())
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

void GameRoom::create()
{
    this->_thread = std::thread(&GameRoom::run, this);
}

void GameRoom::run()
{
    this->waitStart();
    while (this->_loop) {
        this->runStage();

        TimePoint now = steadyClock::now();
        if (0 == _enemyLastRefresh.time_since_epoch().count()
            || (size_t)DURATION_CAST(now - _enemyLastRefresh).count() > _enemyRefreshFreq) {
            this->updateEnemy();
            _enemyLastRefresh = now;
        }
    }
}

void GameRoom::destroy()
{
    if (this->_thread.joinable()) {
        this->_loop = false;
        this->_thread.join();
    }
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

void GameRoom::factoryStage(const StageStep &step)
{
    switch (step._type) {
        case EntityType::ENEMY: {
            std::pair<int, int> velocityEnemy = ServerCore::config->getVar<std::pair<int, int>>("ENEMY_DEFAULT_VELOCITY");
            ServerCore::network->createEntity(_id, "Enemy", netVector2f(step._pos.first, step._pos.second), netVector2f(velocityEnemy.first, velocityEnemy.second));
            this->_enemyRequest.push(EnemyRequest(step._aiPath, step._pos.first, step._pos.second));
            break;
        }
        case EntityType::EQUIPMENT: {
            std::pair<int, int> velocityEquipment = ServerCore::config->getVar<std::pair<int, int>>("EQUIPMENT_DEFAULT_VELOCITY");
            ServerCore::network->createEntity(_id, "Equipment", netVector2f(step._pos.first, step._pos.second), netVector2f(velocityEquipment.first, velocityEquipment.second));
            break;
        }
        default:
            throw std::invalid_argument("Invalid EntityType -> None register");
            break;
    }
}

void GameRoom::updateEnemy()
{
    this->_stateMachine.runAllMachines();

    auto listHealth = this->_stateMachine.retreiveHealthComponents();
    auto listVel = this->_stateMachine.retreiveVelComponents();
    auto listPos = this->_stateMachine.retreivePosComponents();
    auto listId = this->_stateMachine.retreiveNetworkId();

    if (listHealth.size() != listVel.size() || listHealth.size() != listPos.size() || listHealth.size() != listId.size())
        throw std::invalid_argument("Invalid state machine value, vector have various size");
    for (size_t it = 0; it < listId.size(); it++) {
        ServerCore::network->syncComponent(_id, listId[it], Component::Health::type, sizeof(Component::Health), &(listHealth[it]));
        ServerCore::network->syncComponent(_id, listId[it], Engine::Velocity::type, sizeof(Engine::Velocity), &(listVel[it]));
        ServerCore::network->syncComponent(_id, listId[it], Engine::Position::type, sizeof(Engine::Position), &(listPos[it]));
    }
}

void GameRoom::createEntityEnemy(uint32_t networkId)
{
    if (!this->_enemyRequest.size())
        throw std::invalid_argument("Request enemy queue is empty, we can't create enemy");

    // CREATE MACHINE
    const EnemyRequest &request = this->_enemyRequest.front();
    IEnemyApi *api = this->_stateMachine.loadEnemyApi(request.path, request.position);

    this->_enemyRequest.pop();
    this->_stateMachine.setMachineNetworkId(api, networkId);
    
    // SYNC BASIC
    auto basic = this->_stateMachine.retreiveBasicComponents(api);
    ServerCore::network->syncComponent(_id, networkId, Component::AnimationInfo::type, sizeof(Component::AnimationInfo),
        &(basic.first));
}

void GameRoom::destroyEntityEnemy(uint32_t networkId)
{
    this->_stateMachine.closeEnemyApi(this->_stateMachine.getEnemyApi(networkId));
}

void GameRoom::waitStart()
{
    while (GET_NOW < _timeStartRun);
    this->_start = std::chrono::system_clock::now();
}