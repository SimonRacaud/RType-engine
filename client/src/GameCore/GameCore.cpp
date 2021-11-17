/*
** EPITECH PROJECT, 2021
** GameCore
** File description:
** GameCore.cpp
*/


#include <iostream>
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "GameCore.hpp"
#include "global.hpp"

#include "ConfigFileExternal/ConfigFileExternal.hpp"

#include "Scene/Start/StartScene.hpp"
#include "Scene/Debug/DebugScene.hpp"
#include "Scene/Game/GameScene.hpp"
#include "Scene/Home/HomeScene.hpp"
#include "Scene/RoomList/RoomListScene.hpp"
#include "Scene/Settings/SettingsScene.hpp"

#include "System/LogPosition/LogPositionSystem.hpp"

#include "Event/AudioEvent/AudioEventLoad.hpp"
#include "Event/AudioEvent/AudioEventPlay.hpp"
#include "Event/AudioEvent/AudioEventVolume.hpp"
#include "Component/Render.hpp"
#include "Component/Scroll.hpp"
#include "Component/Shooting.hpp"
#include "Components/EntityMask.hpp"
#include "Component/InputEvent.hpp"
#include "Component/EnemyType.hpp"
#include "Component/SyncSend.hpp"
#include "Component/Damage.hpp"

#include "System/NetworkReceive/NetworkReceiveSystem.hpp"
#include "System/RenderSystem/RenderSystem.hpp"
#include "System/ScrollSystem/ScrollSystem.hpp"
#include "System/SyncSendSystem/SyncSendSystem.hpp"
#include "System/OutofBoundsSystem/OutofBoundsSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "SfmlApiManager/SfmlApiManager.hpp"
#include "SfmlApiManager/SfmlApiManager.cpp"

//SfmlApiManager *sfmlManagerEntry = DLLoader<SfmlApiManager>::getEntryPoint("./build/lib/libSfml.so", "initApi");
Engine::IGameEngine &GameCore::engine = Engine::EngineFactory::getInstance();
std::shared_ptr<IWindowManager> GameCore::window = std::make_shared<WindowManager>();
std::unique_ptr<IEventManager> GameCore::event = std::make_unique<EventManager>();
std::unique_ptr<ConfigFile> GameCore::config = std::make_unique<ConfigFile>("client.config");
ClientNetworkCore GameCore::networkCore = ClientNetworkCore(GameCore::engine);
EntityFactory GameCore::entityFactory = EntityFactory(Engine::ClusterName::GAME);

GameCore::GameCore()
{
    config->setVarGetter<vector2D>(ConfigFileExternal::getVector2D);
    window->setName(config->getVar<std::string>("WINDOW_NAME"));
    window->setFramerateLimiter(config->getVar<int>("WINDOW_FAMERATE"));
    window->setSize(config->getVar<vector2D>("WINDOW_SIZE"));
    window->open();
}

GameCore::~GameCore()
{
}

void GameCore::run()
{
    //reg->registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/song.ogg");
    //reg->registerEvent<AudioEventVolume>("asset/music/song.ogg", 100);
    //reg->registerEvent<AudioEventPlay>("asset/music/song.ogg");

    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Timer>();
    componentManager.registerComponent<Engine::Render>();
    componentManager.registerComponent<Engine::Hitbox>();
    componentManager.registerComponent<Engine::Hitbox>();
    componentManager.registerComponent<Engine::Position>();
    componentManager.registerComponent<Engine::Velocity>();
    componentManager.registerComponent<Engine::InputEvent>();
    componentManager.registerComponent<Engine::ScoreComponent>();
    componentManager.registerComponent<Engine::NumberComponent>();
    componentManager.registerComponent<Engine::EquipmentComponent>();
    componentManager.registerComponent<Engine::SizeComponent>();
    componentManager.registerComponent<Component::Scroll>();
    componentManager.registerComponent<Component::Shooting>();
    componentManager.registerComponent<Component::EntityMask>();
    componentManager.registerComponent<Component::SyncSend>();
    componentManager.registerComponent<Component::EnemyType>();
    componentManager.registerComponent<Component::Damage>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<System::RenderSystem>();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<System::InputEventSystem>();
    systemManager.registerSystem<System::LogPositionSystem>();
    systemManager.registerSystem<Engine::ColliderSystem>();
    systemManager.registerSystem<Engine::TimerSystem>();
    systemManager.registerSystem<System::ScrollSystem>();
    systemManager.registerSystem<System::NetworkReceiveSystem>();
    systemManager.registerSystem<System::SyncSendSystem>();
    systemManager.registerSystem<System::OutofBoundsSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    sceneManager.registerScene<Scene::StartScene>();
    sceneManager.registerScene<Scene::HomeScene>();
    sceneManager.registerScene<Scene::SettingsScene>();
    sceneManager.registerScene<Scene::RoomListScene>();
    sceneManager.registerScene<Scene::GameScene>();
    sceneManager.registerScene<Scene::DebugScene>("Test");

    sceneManager.select<Scene::GameScene>();

    engine.exec();
}