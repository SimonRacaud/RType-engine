/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PATHGETTER
*/

#ifndef PATHGETTER_HPP_
#define PATHGETTER_HPP_

#include <filesystem>
#include <string>

class PathGetter {
	public:
		PathGetter() = delete;
		~PathGetter() = delete;
		
		static std::string getPath(std::string &str);
};

#endif /* !PATHGETTER_HPP_ */
