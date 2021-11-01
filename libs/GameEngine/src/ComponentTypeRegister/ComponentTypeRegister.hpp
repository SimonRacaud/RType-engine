/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 ComponentTypeRegister.hpp.h
*/

#ifndef COMPONENTTYPEREGISTER_HPP
#define COMPONENTTYPEREGISTER_HPP

#include "IComponentTypeRegister.hpp"
#include "global.hpp"
#include "Exception/InvalidParameterException.hpp"

#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>

namespace Engine
{
    using std::size_t;

    template <typename ComponentType>
    class ComponentTypeRegister : public IComponentTypeRegister {
      public:
        ComponentTypeRegister(std::vector<Signature> &signatures);
        virtual ~ComponentTypeRegister() = default;

        virtual void allocate(size_t size) override;

        ComponentType &get(Entity entity);

        template <typename... Args> void add(Entity entity, Args &&...args);

        virtual void remove(Entity entity) override;
        Entity getOwner(const ComponentType &component);

        std::vector<ComponentType> &getComponents();

      private:
        std::vector<ComponentType> _components;
        std::vector<Entity> _componentOwners;
        std::unordered_map<Entity, size_t> _entityToComponent;
        std::vector<Signature> &_entitySignatures;
    };

    template <typename T>
    ComponentTypeRegister<T>::ComponentTypeRegister(std::vector<Signature> &signatures)
        : _entitySignatures(signatures)
    {
    }

    template <typename T> void ComponentTypeRegister<T>::allocate(std::size_t size)
    {
        _components.reserve(size);
        _componentOwners.reserve(size);
        _entityToComponent.reserve(size);
    }

    template <typename T> T &ComponentTypeRegister<T>::get(Entity entity)
    {
        return _components[_entityToComponent[entity]];
    }

    template <typename T> template <typename... Args> void ComponentTypeRegister<T>::add(Entity entity, Args &&...args)
    {
        auto index = static_cast<size_t>(_components.size());

        _components.emplace_back(std::forward<Args>(args)...);
        _componentOwners.emplace_back(entity);
        _entityToComponent[entity] = index;
        _entitySignatures[entity][T::type] = true;
    }

    template <typename T> void ComponentTypeRegister<T>::remove(Entity entity)
    {
        if (!_entitySignatures[entity][T::type]) {
            throw InvalidParameterException("Component doesn't exist");
        }
        _entitySignatures[entity][T::type] = false;
        auto index = _entityToComponent[entity];
        // update _components
        _components[index] = std::move(_components.back());
        _components.pop_back();
        // update _entityToComponent
        _entityToComponent[_componentOwners.back()] = index;
        _entityToComponent.erase(entity);
        // update _componentOwners
        _componentOwners[index] = _componentOwners.back();
        _componentOwners.pop_back();
    }

    template <typename T> Entity ComponentTypeRegister<T>::getOwner(const T &component)
    {
        auto begin = _components.data();
        auto index = static_cast<std::size_t>(&component - begin);
        return _componentOwners[index];
    }

    template <typename T> std::vector<T> &ComponentTypeRegister<T>::getComponents()
    {
        return _components;
    }

} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP