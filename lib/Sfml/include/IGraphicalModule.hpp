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
        template <typename... buildParams> void addObject(const defaultType &type, buildParams &&... params);
        virtual void removeObject(const tokenType &) = 0;
        virtual bool isOpen() const = 0;
        virtual void play() = 0;
};

#endif