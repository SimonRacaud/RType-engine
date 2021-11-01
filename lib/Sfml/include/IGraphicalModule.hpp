/*
** PERSONAL PROJECT, 2021
** IGraphicalModule
** File description:
** IGraphicalModule.hpp
*/

#ifndef IGRAPHICALMODULE_HPP
#define IGRAPHICALMODULE_HPP

template<typename tokenType>
class IGraphicalModule
{
    public:
        ~IGraphicalModule() = default;
        virtual void addObject(GenericObject<tokenType> &&);
        virtual void removeObject(const tokenType &);
        virtual void play();
};

#endif