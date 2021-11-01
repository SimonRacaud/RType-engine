/*
** PERSONAL PROJECT, 2021
** GetterObject
** File description:
** GetterObject.hpp
*/

#ifndef GETTEROBJECT_HPP
#define GETTEROBJECT_HPP

#include "GenericObject.hpp"
#include <string>

class GetterObject
{
    public:
        static GenericObject<std::string> getObjectAudio(const std::string &token, ...);
        static GenericObject<std::string> getObjectSprite(const std::string &token, ...);
        static GenericObject<std::string> getObjectKeyEvent(const std::string &token, ...);
        static GenericObject<std::string> getObjectWindow(const std::string &token, ...);
        static GenericObject<std::string> getObjectAnimation(const std::string &token, ...);
};

#endif