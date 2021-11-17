/*
** EPITECH PROJECT, 2021
** GameCore
** File description:
** GameCore.hpp
*/

#ifndef GAMECORE_HPP
#define GAMECORE_HPP

#include "ConfigFile.hpp"

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"

#include "build.hpp"
#include "EventManager/EventManager.hpp"
#include "WindowManager/WindowManager.hpp"
#include "Event/AudioEvent/AudioEventManager/AudioEventManager.hpp"
#include "Event/EmptyCluster/EmptyClusterManager/EmptyClusterManager.hpp"
#include "Event/NetworkEvent/NetworkEventManager/NetworkEventManager.hpp"
#include "Event/GUI/GuiEventManager.hpp"
#include "DLLoader.hpp"
#include "ClientNetworkCore/ClientNetworkCore.hpp"
#include "EntityFactory/EntityFactory.hpp"

class GameCore
{
    public:
        GameCore();
        GameCore(const GameCore &) = delete;
        ~GameCore();

        void run();

    public:
        static Engine::IGameEngine &engine;
        static std::shared_ptr<IWindowManager> window;
        static std::unique_ptr<IEventManager> event;
        static std::unique_ptr<ConfigFile> config;
        static ClientNetworkCore networkCore;
        static EntityFactory entityFactory;
  private:
        AudioEventManager _audio;
        NetworkEventManager _network;
        GuiEventManager _guiEventManager;
        EmptyClusterManager _emptyCluster;
};

#endif