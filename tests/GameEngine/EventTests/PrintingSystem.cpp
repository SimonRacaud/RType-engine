/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PrintingSystem
*/

#include "PrintingSystem.hpp"

PrintingSystem::PrintingSystem()
{
	std::function<void(const PrintEvent *)> func = printCallback;
	if (reg == nullptr)
		std::cout << " register is null" << std::endl;
	else
		reg->registerCallback(func);
}

PrintingSystem::~PrintingSystem()
{
}

void PrintingSystem::printCallback(const PrintEvent *e)
{
	std::cout << e->_toPrint << std::endl;
}