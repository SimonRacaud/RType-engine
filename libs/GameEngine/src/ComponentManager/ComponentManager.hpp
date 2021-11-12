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
#include <vector>
#include <array>
#include "BaseComponent/BaseComponent.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "EntityName.hpp"
#include "global.hpp"
#include "EntityManager/EntityManager.hpp"
#include "Exception/NotRegisteredException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/FatalErrorException.hpp"
#include "Engine/EngineFactory.hpp"
#include "FactoryShortcuts.hpp"

namespace Engine
{
    #define GET_ENTITY_M Engine::EngineFactory::getInstance().getEntityManager()

    using std::array;
    using std::size_t;
    using std::shared_ptr;
    using std::unique_ptr;
    using std::vector;

    class ComponentManager {
      public:
        /**
         * \brief Access to the component register
         */
        friend class EntityManager;

        ComponentManager();
        virtual ~ComponentManager() = default;

        /**
         * \brief Register's array allocation.
         */
        void allocate();

        /**
         * \brief add a component to the Engine
         * @tparam ComponentType
         */
        template <typename ComponentType> void registerComponent();

        /**
         * @brief Get a component of a specific entity
         * @throws NotFoundException
         * @tparam ComponentType
         * @param entity
         * @return ComponentType
         */
        template <typename ComponentType> ComponentType &get(Entity entity);

        /**
         * @brief Get component(s) of a specific entity
         * @throws NotFoundException
         * @tparam ComponentTypeList
         * @param entity
         * @return tuple<ComponentType>
         */
        template <typename... ComponentTypeList>
        std::tuple<ComponentTypeList &...> getList(Entity entity);

        /**
         * @brief Attach a component to a specific entity
         * @throws FatalErrorException
         * @throws NotRegisteredException
         * @throws NotFoundException
         * @tparam ComponentType
         * @tparam Args
         * @param entity
         * @param args Arguments of the component's constructor
         */
        template <typename ComponentType, typename... Args>
        void add(Entity entity, Args &&...args);

        /**
         * @brief Remove a component of a specific entity
         * @throws InvalidParameterException
         * @tparam ComponentType
         * @param entity
         */
        template <typename ComponentType> void remove(Entity entity);
        /**
         * @brief Remove a component of a named entity
         * @throws InvalidParameterException
         * @tparam ComponentType
         * @param name
         */
        template <typename ComponentType> void remove(EntityName name);

        /**
         * @brief Get the id of the entity that own a specific component
         * @throws NotFoundException
         * @tparam ComponentType
         * @param component
         * @return
         */
        template <typename ComponentType>
        Entity getOwner(const ComponentType &component) const;

        /**
         * @brief Do an action on every instances of a component type
         * @tparam ComponentType
         * @param fn
         */
        template <typename ComponentType>
        void foreachComponent(ComponentBrowseFunction<ComponentType> fn);

        /**
         * @brief Do the entity has a component ComponentType ?
         * @tparam ComponentType
         * @param entity
         * @return
         */
        template <typename ComponentType>
        bool hasComponent(Entity entity);
        /**
         * @brief Do the entity has every components ComponentTypeList ?
         * @tparam ComponentTypeList
         * @param entity
         * @return
         */
        template <typename... ComponentTypeList>
        bool hasComponents(Entity entity);

      private:
        template <typename ComponentType> void _checkType() const;
        template <typename... ComponentTypeList> void _checkTypeList() const;

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer();

        template <typename ComponentType>
        ComponentTypeRegister<ComponentType> *getComponentContainer() const;

      private:
        array<shared_ptr<IComponentTypeRegister>, MAX_COMPONENT_TYPE>
            _componentRegisters;
        size_t _componentTypeCount{0};
    };

    template <typename ComponentType>
    bool ComponentManager::hasComponent(Entity entity)
    {
        this->_checkType<ComponentType>();
        return GET_ENTITY_M._getSignature(entity)[ComponentType::getIndex()];
    }

    template <typename... ComponentTypeList>
    bool ComponentManager::hasComponents(Entity entity)
    {
        (this->_checkTypeList<ComponentTypeList>(), ...);
        Signature requirements = Signature();
        (requirements.set(ComponentTypeList::getIndex()), ...);
        return (requirements & GET_ENTITY_M._getSignature(entity)) == requirements;
    }

    template <typename ComponentType>
    void ComponentManager::registerComponent()
    {
        this->_checkType<ComponentType>();
        // Set idx
        ComponentType::setIndex(_componentTypeCount);
        this->_componentTypeCount++;
        // Create register
        vector<Signature> &signatures = GET_ENTITY_M._getSignatureList();
        _componentRegisters[ComponentType::getIndex()] =
            std::make_shared<ComponentTypeRegister<ComponentType>>(signatures);
    }

    template <typename ComponentType>
    ComponentType &ComponentManager::get(Entity entity)
    {
        this->_checkType<ComponentType>();
        if (this->hasComponent<ComponentType>(entity) == false) {
            std::cerr << "ComponentManager::getComponent Entity " <<
                entity << " request " << ComponentType::type.name() << " component."
                      << std::endl;
            throw NotFoundException(
                "ComponentManager::getComponent The entity "
                "don't have the requested component.");
        }
        return this->getComponentContainer<ComponentType>()->get(entity);
    }

    template <typename... ComponentTypeList>
    std::tuple<ComponentTypeList &...> ComponentManager::getList(Entity entity)
    {
        this->_checkTypeList<ComponentTypeList...>();
        if (this->hasComponents<ComponentTypeList...>(entity) == false) {
            ((std::cerr << "ComponentManager::getComponents Entity " <<
                 entity << " request " << ComponentTypeList::getIndex()
                        << " component." << std::endl), ...);
            throw NotFoundException(
                "ComponentManager::getComponents The entity "
                "don't have the requested Components.");
        }
        return std::tie(
            this->getComponentContainer<ComponentTypeList>()->get(entity)...);
    }

    template <typename ComponentType, typename... Args>
    void ComponentManager::add(Entity entity, Args &&...args)
    {
        this->_checkType<ComponentType>();
        if (_componentRegisters[ComponentType::getIndex()] == nullptr) {
            throw NotRegisteredException("Component type not registered");
        }
        if (this->hasComponent<ComponentType>(entity)) {
            std::cerr << "ComponentManager::addComponent : Entity "
                      << entity << " => Component " <<
                      ComponentType::getIndex() << std::endl;
            throw FatalErrorException("ComponentManager::addComponent, Same "
                                        "component added several time"
                                        "on an entity.");
        }
        this->getComponentContainer<ComponentType>()->add(
            entity, std::forward<Args>(args)...);
        // Send message to system
        const Signature &signature = GET_ENTITY_M._getSignature(entity);
        GET_SYS_M._onEntityUpdated(entity, signature);
        SHOW_DEBUG_COMPONENT("Component: create for entity id=" + std::to_string(entity)
            + ", component type=" + TYPE_STR(ComponentType::type));
    }

    template <typename ComponentType>
    void ComponentManager::remove(Entity entity)
    {
        this->_checkType<ComponentType>();
        if (this->hasComponent<ComponentType>(entity) == false) {
            throw InvalidParameterException(
                "ComponentManager::remove The "
                "entity don't have the component.");
        }
        this->getComponentContainer<ComponentType>()->remove(entity);
        // Send message to systems
        const auto &signature = GET_ENTITY_M._getSignature(entity);
        GET_SYS_M._onEntityUpdated(entity, signature);
    }

    template <typename ComponentType>
    void ComponentManager::remove(EntityName name)
    {
        Entity entity = GET_ENTITY_M.getId(name);

        this->remove<ComponentType>(entity);
    }

    template <typename ComponentType>
    Entity ComponentManager::getOwner(const ComponentType &component) const
    {
        this->_checkType<ComponentType>();
        return this->getComponentContainer<ComponentType>()->getOwner(component);
    }

    template <typename ComponentType>
    void ComponentManager::foreachComponent(
        ComponentBrowseFunction<ComponentType> fn)
    {
        this->_checkType<ComponentType>();
        vector<unique_ptr<ComponentType>> &components =
            this->getComponentContainer<ComponentType>()->getComponents();

        std::for_each(components.begin(), components.end(), fn);
    }

    template <typename ComponentType> void ComponentManager::_checkType() const
    {
        static_assert(std::is_base_of<BaseComponent<ComponentType>,
                          ComponentType>::value,
            "Invalid component type");
    }

    template <typename... ComponentTypeList>
    void ComponentManager::_checkTypeList() const
    {
        (this->_checkType<ComponentTypeList>(), ...);
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer()
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::getIndex()].get());
    }

    template <typename ComponentType>
    ComponentTypeRegister<ComponentType> *
    ComponentManager::getComponentContainer() const
    {
        return static_cast<ComponentTypeRegister<ComponentType> *>(
            _componentRegisters[ComponentType::getIndex()].get());
    }
} // namespace Engine

#endif // COMPONENTMANAGER_HPP
