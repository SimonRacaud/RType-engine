/*
** EPITECH PROJECT, 2021
** RType
** File description:
** main
*/

#include "PrintEvent.hpp"
#include "PrintingSystem.hpp"
#include "global.hpp"


//The reg variable will in the end be the Engine object. That holds a pointer to a EventCallBackRegister
//For this example I made the register global to facilitate the test
int main(void)
{
	init();

	if (reg) {
		PrintingSystem sys;
		reg->dispatch<PrintEvent>("this works great");
	}
	reg->execQueue();
	return 0;
}