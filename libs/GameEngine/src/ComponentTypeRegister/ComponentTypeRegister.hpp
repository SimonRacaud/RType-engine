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
#include "Exception/NotFoundException.hpp"

#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>
#include <algorithm>

namespace Engine
{
    using std::size_t;
    using std::unique_ptr;
    using std::tuple;
    using std::vector;

    /**
     * @brief That class manage the instances of a component
     * @tparam ComponentType
     */
    template <typename ComponentType>
    class ComponentTypeRegister : public IComponentTypeRegister {
      public:
        /**
         * @param signatures : Signatures of every entities of the ECS
         */
        explicit ComponentTypeRegister(std::vector<Signature> &signatures);
        virtual ~ComponentTypeRegister() = default;

        /**
         * @brief Memory optimisation : pre-allocation of the containers
         * @param size
         */
        virtual void allocate(size_t size) override;

        /**
         * @brief Get the instance attached to an entity
         * @throws NotFoundException
         * @param entity
         * @return
         */
        ComponentType &get(Entity entity);

        template <typename... Args> void add(Entity entity, Args &&...args);

        /**
         * @throws InvalidParameterException
         * @param entity
         */
        virtual void remove(Entity entity) override;
        /**
         * @throws NotFoundException
         * @param component
         * @return
         */
        Entity getOwner(const ComponentType &component);

        /**
         * @brief Reference to the list of the instances
         * @return
         */
        vector<ComponentType *> &getComponents();

      private:
        Signature &_getComponentSignature(Entity entity);

      private:
        std::vector<ComponentType *> _components;
        std::vector<Entity> _componentOwners;
        std::unordered_map<Entity, size_t> _entityToComponent;
        std::vector<Signature> &_entitySignatures;
    };

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType>::ComponentTypeRegister(std::vector<Signature> &signatures)
        : _entitySignatures(signatures)
    {}

    template <typename ComponentType>
    void ComponentTypeRegister<ComponentType>::allocate(std::size_t size)
    {
        _components.reserve(size);
        _componentOwners.reserve(size);
        _entityToComponent.reserve(size);
    }

    template <typename ComponentType>
    ComponentType &ComponentTypeRegister<ComponentType>::get(Entity entity)
    {
        try {
            size_t componentIdx = _entityToComponent.at(entity);

            return *_components[componentIdx];
        } catch (std::out_of_range const &) {
            throw NotFoundException("ComponentTypeRegister::get Entity not found");
        }
    }

    template <typename ComponentType>
    template <typename... Args>
    void ComponentTypeRegister<ComponentType>::add(Entity entity, Args &&...args)
    {
        size_t index = static_cast<size_t>(_components.size());

        _components.push_back(new ComponentType(std::forward<Args>(args)...));
        _componentOwners.push_back(entity);
        _entityToComponent[entity] = index;
        this->_getComponentSignature(entity)[ComponentType::getIndex()] = true;
    }

    template <typename ComponentType>
    void ComponentTypeRegister<ComponentType>::remove(Entity entity)
    {
        Signature &signature = this->_getComponentSignature(entity);

        if (false == signature[ComponentType::getIndex()]) {
            throw InvalidParameterException("ComponentTypeRegister::remove Component doesn't exist");
        }
        signature[ComponentType::getIndex()] = false;
        Index index = (Index)_entityToComponent[entity];
        // update _components slot
        delete _components[index];
        _components[index] = _components.back();
        _components.pop_back();
        // update _entityToComponent
        _entityToComponent[_componentOwners.back()] = index;
        _entityToComponent.erase(entity);
        // update _componentOwners
        _componentOwners[index] = _componentOwners.back();
        _componentOwners.pop_back();
        SHOW_DEBUG_COMPONENT("Component: remove for entity id=" + std::to_string(entity)
            + ", component type=" + TYPE_STR(ComponentType::type));
    }

    template <typename ComponentType>
    Entity ComponentTypeRegister<ComponentType>::getOwner(const ComponentType &component)
    {
        /// Search instance
        auto it = std::find_if(_components.begin(), _components.end(),
            [component](ComponentType *ptr) {return ptr == &component;});

        if (it == _components.end()) {
            throw NotFoundException("Component instance not found");
        }
        /// Compute the diff between the beginning of the container and the ptr
        auto index = std::distance(_components.begin(), it);

        return _componentOwners[index];
    }

    template <typename ComponentType>
    Signature &ComponentTypeRegister<ComponentType>::_getComponentSignature(Entity entity)
    {
        try {
             return _entitySignatures.at(entity);
        } catch (std::out_of_range const &) {
            throw NotFoundException("Signature not found");
        }
    }

    template <typename ComponentType>
    vector<ComponentType *> &ComponentTypeRegister<ComponentType>::getComponents()
    {
        return _components;
    }

} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP