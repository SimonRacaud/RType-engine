/*
** EPITECH PROJECT, 2021
** RType
** File description:
** global
*/

#include "global.hpp"

Engine::Event::EventCallbackRegister *reg = nullptr;

void init()
{
	if (!reg)
		reg = new Engine::Event::EventCallbackRegister();
}