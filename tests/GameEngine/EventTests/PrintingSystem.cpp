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
	std::function<void(const MultipleEvent *)> func2 = multipleEvents;
	if (reg == nullptr)
		std::cout << " register is null" << std::endl;
	else {
		reg->registerCallback(func);
		reg->registerCallback(func2);
	}
}

PrintingSystem::~PrintingSystem()
{
}

void PrintingSystem::printCallback(const PrintEvent *e)
{
	std::cout << e->_toPrint << std::endl;
}

void PrintingSystem::multipleEvents(const MultipleEvent *e)
{
	if (e->_nb < 0)
		return;
	for (int i = 0; i < e->_nb; i++) {
		reg->registerEvent<PrintEvent>(std::string("[Event # " + std::to_string(i)));
	}
}
