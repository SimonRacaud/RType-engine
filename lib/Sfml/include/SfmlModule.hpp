/*
** PERSONAL PROJECT, 2021
** SfmlModule
** File description:
** SfmlModule.hpp
*/

#ifndef SFMLMODULE_HPP
#define SFMLMODULE_HPP

#include "FactoryObject.hpp"
#include "IGraphicalModule.hpp"
#include "FactoryObject/GetterName/GetterName.hpp"
#include "FactoryObject/GetterObject/GetterObject.hpp"

class SfmlModule: public IGraphicalModule<std::string>
{
    public:
        SfmlModule();
        ~SfmlModule();
        void addObject(GenericObject<std::string> &&);
        void removeObject(const std::string &);
        void play();

    private:
        FactoryObject<std::string> _factory;
};

#endif