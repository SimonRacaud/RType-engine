/*
** EPITECH PROJECT, 2021
** RType
** File description:
** main
*/

#include "PrintEvent.hpp"
#include "PrintingSystem.hpp"
#include "Testglobal.hpp"
#include "MultipleEvent.hpp"

//The reg variable will in the end be the Engine object. That holds a pointer to a EventCallBackRegister
//For this example I made the register global to facilitate the test
int main(void)
{
	init();

	if (reg) {
		PrintingSystem sys;
		reg->registerEvent<PrintEvent>("This is an example of an event firing another event");
		reg->registerEvent<MultipleEvent>(3);
		reg->registerEvent<PrintEvent>("The events are processed directly and added to the queue, they will be executed");
		//Since the event is a queue each event that adds new events, makes these new events be executed last
		//Maybe change it to a list to organise it ?
	}
	reg->execQueue();
	return 0;
}