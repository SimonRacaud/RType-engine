/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.hpp
*/

#ifndef SERVERCORE_HPP
#define SERVERCORE_HPP

#include <memory>
#include "EngineCore.hpp"
#include "ConfigFile.hpp"

class ServerCore
{
    public:
        ServerCore();
        ServerCore(const ServerCore &) = delete;
        ~ServerCore();

        void run(void);

    public:
        static Engine::IGameEngine &engine;
        static std::unique_ptr<ConfigFile> config;
};

#endif