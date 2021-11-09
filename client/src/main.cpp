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

#include "Event/RenderEvent/RenderEventAdd.hpp"
#include "Event/RenderEvent/RenderEventDraw.hpp"
#include "Event/RenderEvent/RenderEventManager/RenderEventManager.hpp"

#include "TextManager/TextManager.hpp"
#include "WindowManager/WindowManager.hpp"

#include "System/InputEventManager/InputEventManager.hpp"

using namespace std;

Engine::IGameEngine &engine = Engine::EngineFactory::getInstance();
Engine::Event::EventCallbackRegister *reg = nullptr;

static void init()
{
	if (!reg)
		reg = new Engine::Event::EventCallbackRegister();
}

int main(void)
{
    init();
    AudioEventManager audio;
    RenderEventManager render;
    std::shared_ptr<IWindowManager> window = std::make_shared<WindowManager>();
    InputEventManager input(window);
    TextManager text;

    reg->registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::MUSIC, "asset/music/song.ogg");
    reg->registerEvent<AudioEventVolume>("asset/music/song.ogg", 100);
    reg->registerEvent<AudioEventPlay>("asset/music/song.ogg");

    text.setColor(ITextManager<renderToolSfml>::color_e::RED);
    text.setContent("mdr");
    text.setFont("asset/font/Code-Bold.ttf");

    reg->registerEvent<RenderEventAdd<std::string>>("one", static_cast<IDrawable<renderToolSfml> *>(&text));

    window->setName("yolo");
    window->setFramerateLimiter(30);
    window->setSize(vector2D(800, 800));
    window->open();

    while (window->isOpen()) {
        window->clear();

        reg->registerEvent<RenderEventDraw>(window);
        reg->execQueue();

        window->refresh();
        input.run();
    }

    Engine::ComponentManager &componentManager = engine.getComponentManager();
    componentManager.registerComponent<Engine::Position>();
    componentManager.registerComponent<Engine::Velocity>();

    Engine::SystemManager &systemManager = engine.getSystemManager();
    systemManager.registerSystem<Engine::PhysicsSystem>();
    systemManager.registerSystem<System::LogPositionSystem>();

    Engine::SceneManager &sceneManager = engine.getSceneManager();
    sceneManager.registerScene<Scene::StartScene>();
    sceneManager.select<Scene::StartScene>();

    engine.exec();
    return EXIT_SUCCESS;
}