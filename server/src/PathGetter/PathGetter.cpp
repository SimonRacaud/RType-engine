/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PathGetter
*/

#include "PathGetter.hpp"



std::string PathGetter::getPath(std::string &str)
{
	bool windows = false;
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || !defined(__CYGWIN__)
		windows = true;
	#endif

		

}