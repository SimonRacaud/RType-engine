/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PrintingSystem
*/

#ifndef PRINTINGSYSTEM_HPP_
#define PRINTINGSYSTEM_HPP_

#include "PrintEvent.hpp"
#include <iostream>
#include "global.hpp"

class PrintingSystem {
	public:
		PrintingSystem();
		~PrintingSystem();
		
		static void printCallback(const PrintEvent *e);
	protected:
	private:
};

#endif /* !PRINTINGSYSTEM_HPP_ */
