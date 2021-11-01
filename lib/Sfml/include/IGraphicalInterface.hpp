/*
** PERSONAL PROJECT, 2021
** IGraphicalInterface
** File description:
** IGraphicalInterface.hpp
*/

#ifndef IGRAPHICALINTERFACE_HPP
#define IGRAPHICALINTERFACE_HPP

template<typename tokenType>
class IGraphicalInterface
{
    public:
        ~IGraphicalInterface() = default;
        virtual void addObject(GenericObject<tokenType> &&);
        virtual void removeObject(const tokenType &);
        virtual void play();
};

#endif