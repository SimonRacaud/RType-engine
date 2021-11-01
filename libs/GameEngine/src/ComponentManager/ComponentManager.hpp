/*
** EPITECH PROJECT , 2021
** ComponentManager
** File description:
** simon
*/

#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include <memory>
#include <algorithm>
#include "BaseComponent.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "EntityName.hpp"
#include "IComponentTypeRegister.hpp"
#include "global.hpp"

namespace Engine
{
    using std::array;
    using std::size_t;
    using std::shared_ptr;

    class ComponentManager {
        friend class EntityManager;

      public:
        ComponentManager();
        virtual ~ComponentManager() = default;

        void allocate(size_t size);
        template <typename ComponentType> void registerComponent();

        template <typename ComponentType> ComponentType &get(Entity entity);

        template <typename... ComponentTypeList>
        std::tuple<ComponentTypeList &...> getList(Entity entity);

        template <typename ComponentType, typename... Args>
        void add(Entity entity, Args &&...args);

        template <typename ComponentType> void remove(Entity entity);
        template <typename ComponentType> void remove(EntityName name);

        template <typename ComponentType>
        Entity getOwner(const ComponentType &component) const;

        template <typename ComponentType, class Function>
        void foreachComponent(Function fn);

      private:
        shared_ptr<IComponentTypeRegister> getRegister();

        template <typename ComponentType> void checkType() const;
        template <typename... ComponentTypeList> void checkTypeList() const;

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer();

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer() const;

      private:
        array<shared_ptr<IComponentTypeRegister>, MAX_COMPONENT_TYPE>
            _componentRegisters;
    };

    template <typename ComponentType>
    void ComponentManager::registerComponent()
    {
        // TODO
        //        this->checkComponentType<ComponentType>();
        //        _componentRegisters[ComponentType::type] =
        //            std::make_shared<ComponentTypeRegister<ComponentType>>(
        //                _entities.getEntitySignatures());
        // component.setIndex(...)
    }

    template <typename ComponentType>
    ComponentType &ComponentManager::get(Entity entity)
    {
        // TODO
        //        this->checkComponentType<ComponentType>();
        //        if (this->hasComponent<ComponentType>(entity) == false) {
        //            std::cerr << "ComponentManager::getComponent Entity " <<
        //            entity
        //                      << " request " << ComponentType::type << " component." <<
        //                      std::endl;
        //            throw std::invalid_argument(
        //                "ComponentManager::getComponent The entity "
        //                "don't have the requested component.");
        //        }
        //        return this->getComponentContainer<ComponentType>()->get(entity);
    }

    template <typename... ComponentTypeList>
    std::tuple<ComponentTypeList &...> ComponentManager::getList(Entity entity)
    {
        // TODO
        //        this->checkComponentTypes<Ts...>();
        //        if (this->hasComponents<Ts...>(entity) == false) {
        //            ((std::cerr << "ComponentManager::getComponents Entity "
        //            << entity
        //                        << " request " << Ts::type << " component."
        //                        << std::endl),
        //                ...);
        //            throw std::invalid_argument(
        //                "ComponentManager::getComponents The entity "
        //                "don't have the requested Components.");
        //        }
        //        return
        //        std::tie(this->getComponentContainer<Ts>()->get(entity)...);
    }

    template <typename ComponentType, typename... Args>
    void ComponentManager::add(Entity entity, Args &&...args)
    {
        // TODO
        //        this->checkComponentType<ComponentType>();
        //        if (_componentRegisters[ComponentType::type] == nullptr) {
        //            throw std::invalid_argument(
        //                "Invalid component type (not registered?)");
        //        }
        //        if (this->hasComponent<ComponentType>(entity)) {
        //            std::cerr << "ComponentManager::addComponent : Entity "
        //                      << (uint) entity << " => BaseComponent N " <<
        //                      ComponentType::type
        //                      << std::endl;
        //            throw
        //            std::invalid_argument("ComponentManager::addComponent,
        //            Same "
        //                                        "component added several time
        //                                        " "on an entity.");
        //        }
        //        this->getComponentContainer<ComponentType>()->add(
        //            entity, std::forward<Args>(args)...);
        //        // Send message to system
        //        const Signature &signature = _entities.getSignature(entity);
        //        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename ComponentType>
    void ComponentManager::remove(Entity entity)
    {
        // TODO
        //        this->checkComponentType<ComponentType>();
        //        if (this->hasComponent<ComponentType>(entity) == false) {
        //            throw std::invalid_argument(
        //                "ComponentManager::removeComponent, the "
        //                "entity don't have ComponentType component.");
        //        }
        //        this->getComponentContainer<ComponentType>()->remove(entity);
        //        // Send message to systems
        //        const auto &signature = _entities.getSignature(entity);
        //        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename ComponentType>
    void ComponentManager::remove(EntityName name)
    {
        // TODO
    }

    template <typename ComponentType>
    Entity ComponentManager::getOwner(const ComponentType &component) const
    {
        // TODO
        //        this->checkComponentType<ComponentType>();
        //        return this->getComponentContainer<ComponentType>()->getOwner(component);
    }

    template <typename ComponentType> void ComponentManager::checkType() const
    {
        static_assert(std::is_base_of<BaseComponent<ComponentType>,
                          ComponentType>::value,
            "Invalid component type");
    }

    template <typename... ComponentTypeList>
    void ComponentManager::checkTypeList() const
    {
        (this->checkType<ComponentTypeList>(), ...);
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer()
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::type].get());
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer() const
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::type].get());
    }

    template <typename ComponentType, class Function>
    void ComponentManager::foreachComponent(Function fn)
    {
        this->checkType<ComponentType>();
        std::vector<ComponentType> &components =
            this->getComponentContainer<ComponentType>()->getComponents();

        std::for_each(components.begin(), components.end(), fn);
    }
} // namespace Engine

#endif // COMPONENTMANAGER_HPP
