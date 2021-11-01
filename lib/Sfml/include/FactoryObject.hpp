/*
** PERSONAL PROJECT, 2021
** FactoryObject
** File description:
** FactoryObject.hpp
*/

#ifndef FACTORYOBJECT_HPP
#define FACTORYOBJECT_HPP

#include "enum.hpp"
#include "GenericObject/GenericObject.hpp"
#include <functional>
#include <unordered_map>

template<typename tokenType, typename... constructorParams>
class FactoryObject
{
    public:
        FactoryObject()
        {
        }

        ~FactoryObject()
        {
            this->_getterName.clear();
            this->_builder.clear();
        }

        void addToList(const defaultType &key, std::function<tokenType ()> func)
        {
            this->_getterName[key] = func;
        }

        void addToList(const defaultType &key, std::function<GenericObject<tokenType> (const tokenType &, constructorParams &&...)> func)
        {
            this->_builder[key] = func;
        }

        GenericObject<tokenType> builderFactory(const defaultType &key, constructorParams &&... params)
        {
            tokenType token = this->_getterName.at(key)();

            return this->_builder(token, params...);
        }

    private:
        std::unordered_map<defaultType, std::function<tokenType ()>> _getterName;
        std::unordered_map<defaultType, std::function<GenericObject<tokenType> (const tokenType &, constructorParams &&...)>> _builder;
};

#endif