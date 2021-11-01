/*
** PERSONAL PROJECT, 2021
** FactoryObject
** File description:
** FactoryObject.hpp
*/

#ifndef FACTORYOBJECT_HPP
#define FACTORYOBJECT_HPP

#include "enum.hpp"
#include <functional>
#include <unordered_map>

template<typename tokenType>
class FactoryObject
{
    public:
        template <typename... constructorParams> GenericObject<tokenType> builderFactory(const defaultType &key, constructorParams &&... params)
        {
            tokenType token = this->_getterName.at(key)();

            return this->_builder(token, std::forward<constructorParams>(params)...)
        }

    private:
        std::unordered_map<defaultType, std::function<tokenType ()>> _getterName;
        std::unordered_map<defaultType, std::function<GenericObject<tokenType> (const tokenType &, ...)>> _builder;
};

#endif