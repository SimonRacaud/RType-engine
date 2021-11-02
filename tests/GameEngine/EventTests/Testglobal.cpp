/*
** EPITECH PROJECT, 2021
** RType
** File description:
** global
*/

#include "global.hpp"

Engine::Event::EventCallBackRegister *reg = nullptr;

void init()
{
	if (!reg)
		reg = new Engine::Event::EventCallBackRegister();
}