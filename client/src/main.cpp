/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include <iostream>
#include "global.hpp"
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "Scene/Start/StartScene.hpp"
#include "System/LogPosition/LogPositionSystem.hpp"

#include "Event/AudioEvent/AudioEventLoad.hpp"
#include "Event/AudioEvent/AudioEventPlay.hpp"
#include "Event/AudioEvent/AudioEventVolume.hpp"
#include "Event/AudioEvent/AudioEventManager/AudioEventManager.hpp"

#include "build.hpp"

#include "TextManager/TextManager.hpp"
#include "WindowManager/WindowManager.hpp"

#include "Component/Render.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventManager/InputEventManager.hpp"

using namespace std;

Engine::IGameEngine &engine = Engine::EngineFactory::getInstance();
Engine::Event::EventCallbackRegister *reg = nullptr;
std::shared_ptr<IWindowManager> window = nullptr;

static void init()
{
	if (!reg)
		reg = new Engine::Event::EventCallbackRegister();
    if (!window)
		window = std::make_shared<WindowManager>();

    window->setName("yolo");
    window->setFramerateLimiter(30);
    window->setSize(vector2D(800, 800));
    window->open();
}

int main(void)
{
    init();
    AudioEventManager audio;

    reg->registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/song.ogg");
    reg->registerEvent<AudioEventVolume>("asset/music/song.ogg", 100);
    reg->registerEvent<AudioEventPlay>("asset/music/song.ogg");

    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Position>();
    componentManager.registerComponent<Engine::Velocity>();
    componentManager.registerComponent<Engine::Render>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<System::LogPositionSystem>();
    systemManager.registerSystem<System::RenderSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    sceneManager.registerScene<Scene::StartScene>();
    sceneManager.select<Scene::StartScene>();

    reg->execQueue();
    engine.exec();
    return EXIT_SUCCESS;
}