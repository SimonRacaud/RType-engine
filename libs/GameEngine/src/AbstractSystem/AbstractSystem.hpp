/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 AbstractSystem.hpp.h
*/

#ifndef ABSTRACTSYSTEM_HPP
#define ABSTRACTSYSTEM_HPP

#include <cctype>
#include <vector>
#include "SystemPriority.hpp"
#include "env.hpp"
#include "global.hpp"
#include <unordered_map>
#include "IAbstractSystem.hpp"

namespace Engine
{
    template <class SystemType> class AbstractSystem : public IAbstractSystem {
      public:
        AbstractSystem(Time runningFreq = (Time) DEF_SYSTEM_RUN_FREQ,
            SystemPriority priority = SystemPriority::MEDIUM);

        virtual ~AbstractSystem() = default;

        SystemPriority getPriority() const;
        TypeIdx getType() const;

        /**
         * \brief Execute the logic of the class
         */
        virtual void run() = 0;

        /**
         * \brief Do the system need to be executed? (running frequency)
         */
        bool refresh();

        template <typename... ComponentTypeList> void setRequirements();

        void onEntityUpdated(Entity entity, const Signature &components);
        void onEntityRemoved(Entity entity);
        /**
         * \brief optional - to override - define action on adding
         */
        virtual void onManagedEntityAdded(Entity);
        /**
         * \brief optional - to override - define action on removing
         */
        virtual void onManagedEntityRemoved(Entity);

        /**
         * \brief unique id of the system
         */
        static const TypeIdx type;

      protected:
        const std::vector<Entity> &getManagedEntities() const;

      private:
        void attachEntity(Entity entity);
        void detachEntity(Entity entity);

      private:
        Time _runningFrequency;
        SystemPriority _priority;
        Signature _requirements; // required components
        std::vector<Entity> _managedEntities;
        std::unordered_map<Entity, Index> _entityToManagedEntity;
        TimePoint _lastExecTime;
    };
    template <class SystemType>
    const TypeIdx AbstractSystem<SystemType>::type = GET_TYPE_IDX(SystemType);

    template <class SystemType>
    AbstractSystem<SystemType>::AbstractSystem(
        Time runningFreq, SystemPriority priority)
        : _runningFrequency(runningFreq), _priority(priority)
    {
    }

    template <class SystemType>
    SystemPriority AbstractSystem<SystemType>::getPriority() const
    {
        return _priority;
    }

    template <class SystemType>
    TypeIdx AbstractSystem<SystemType>::getType() const
    {
        return AbstractSystem<SystemType>::type;
    }

    template <class SystemType> bool AbstractSystem<SystemType>::refresh()
    {
        // TODO
        return false;
    }

    template <class SystemType>
    template <typename... ComponentTypeList>
    void AbstractSystem<SystemType>::setRequirements()
    {
        (_requirements.set(ComponentTypeList::type), ...);
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::attachEntity(Entity entity)
    {
        _entityToManagedEntity[entity] =
            static_cast<Index>(_managedEntities.size());
        _managedEntities.emplace_back(entity);
        this->onManagedEntityAdded(entity);
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::detachEntity(Entity entity)
    {
        this->onManagedEntityRemoved(entity);
        auto index = _entityToManagedEntity[entity];
        _entityToManagedEntity[_managedEntities.back()] = index;
        _entityToManagedEntity.erase(entity);
        _managedEntities[index] = _managedEntities.back();
        _managedEntities.pop_back();
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::onEntityUpdated(
        Entity entity, const Signature &components)
    {
        bool satisfied = (_requirements & components) == _requirements;
        bool managed = _entityToManagedEntity.find(entity)
            != std::end(_entityToManagedEntity);

        if (satisfied && !managed) {
            this->attachEntity(entity);
        } else if (!satisfied && managed) {
            this->detachEntity(entity);
        }
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::onEntityRemoved(Entity entity)
    {
        if (_entityToManagedEntity.find(entity)
            != _entityToManagedEntity.end()) {
            this->detachEntity(entity);
        }
    }

    template <class SystemType>
    const std::vector<Entity> &
    AbstractSystem<SystemType>::getManagedEntities() const
    {
        return _managedEntities;
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::onManagedEntityAdded(Entity) {}

    template <class SystemType>
    void AbstractSystem<SystemType>::onManagedEntityRemoved(Entity) {}

} // namespace Engine

#endif // ABSTRACTSYSTEM_HPP
