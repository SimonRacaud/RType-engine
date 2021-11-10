/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "GameCore/GameCore.hpp"

Engine::IGameEngine &engine = Engine::EngineFactory::getInstance();
Engine::Event::EventCallbackRegister *reg = nullptr;
std::shared_ptr<IWindowManager> window = nullptr;
std::unique_ptr<IEventManager<renderToolSfml>> event = nullptr;

int main(void)
{
    try {
        GameCore core;

        core.run();
    } catch (...) {
        std::cout << "ERROR: Invalid exit status" << std::endl;
    }
    return EXIT_SUCCESS;
}