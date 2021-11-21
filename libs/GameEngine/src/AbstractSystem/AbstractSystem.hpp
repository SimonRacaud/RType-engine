/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 AbstractSystem.hpp.h
*/

#ifndef ABSTRACTSYSTEM_HPP
#define ABSTRACTSYSTEM_HPP

#include <cctype>
#include <iostream>
#include <vector>
#include "IAbstractSystem.hpp"
#include "SystemPriority.hpp"
#include "env.hpp"
#include "global.hpp"
#include <unordered_map>

namespace Engine
{
    using std::vector;

    template <class SystemType> class AbstractSystem : public IAbstractSystem {
      public:
        explicit AbstractSystem(
            Time runningFreq = (Time) DEF_SYSTEM_RUN_FREQ, SystemPriority systemPriority = SystemPriority::MEDIUM);

        ~AbstractSystem() override = default;

        [[nodiscard]] SystemPriority getPriority() const override;
        [[nodiscard]] TypeIdx getType() const override;

        /**
         * \brief Execute the logic of the class
         */
        void run(const vector<Entity> &entities) override = 0;

        /**
         * \brief Do the system need to be executed? (running frequency)
         */
        bool refresh() override;

        /**
         * \brief technical operations before run(), do not override
         */
        void runSystem() override;

        template <typename... ComponentTypeList> void setRequirements();

        void onEntityUpdated(Entity entity, const Signature &components) override;
        void onEntityRemoved(Entity entity) override;
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
        [[nodiscard]] const std::vector<Entity> &getManagedEntities() const override;

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
    template <class SystemType> const TypeIdx AbstractSystem<SystemType>::type = GET_TYPE_IDX(SystemType);

    template <class SystemType>
    AbstractSystem<SystemType>::AbstractSystem(Time runningFreq, SystemPriority systemPriority)
        : _runningFrequency(runningFreq), _priority(systemPriority)
    {
    }

    template <class SystemType> SystemPriority AbstractSystem<SystemType>::getPriority() const
    {
        return _priority;
    }

    template <class SystemType> TypeIdx AbstractSystem<SystemType>::getType() const
    {
        return AbstractSystem<SystemType>::type;
    }

    template <class SystemType> bool AbstractSystem<SystemType>::refresh()
    {
        TimePoint now = Clock::now();

        if (now - _lastExecTime >= _runningFrequency) {
            _lastExecTime = now;
            return true;
        }
        return false;
    }

    template <class SystemType>
    template <typename... ComponentTypeList>
    void AbstractSystem<SystemType>::setRequirements()
    {
        (_requirements.set(ComponentTypeList::getIndex()), ...);
    }

    template <class SystemType> void AbstractSystem<SystemType>::attachEntity(Entity entity)
    {
        _entityToManagedEntity[entity] = static_cast<Index>(_managedEntities.size());
        _managedEntities.emplace_back(entity);
        this->onManagedEntityAdded(entity);
    }

    template <class SystemType> void AbstractSystem<SystemType>::detachEntity(Entity entity)
    {
        this->onManagedEntityRemoved(entity);
        auto index = _entityToManagedEntity[entity];
        _entityToManagedEntity[_managedEntities.back()] = index;
        _entityToManagedEntity.erase(entity);
        _managedEntities[index] = _managedEntities.back();
        _managedEntities.pop_back();
    }

    template <class SystemType>
    void AbstractSystem<SystemType>::onEntityUpdated(Entity entity, const Signature &components)
    {
        bool satisfied = (_requirements & components) == _requirements;
        bool managed = _entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity);

        if (satisfied && !managed) {
            this->attachEntity(entity);
        } else if (!satisfied && managed) {
            this->detachEntity(entity);
        }
    }

    template <class SystemType> void AbstractSystem<SystemType>::onEntityRemoved(Entity entity)
    {
        if (_entityToManagedEntity.find(entity) != _entityToManagedEntity.end()) {
            this->detachEntity(entity);
        }
    }

    template <class SystemType> const std::vector<Entity> &AbstractSystem<SystemType>::getManagedEntities() const
    {
        return _managedEntities;
    }

    template <class SystemType> void AbstractSystem<SystemType>::onManagedEntityAdded(Entity)
    {
    }

    template <class SystemType> void AbstractSystem<SystemType>::onManagedEntityRemoved(Entity)
    {
    }

    template <class SystemType> void AbstractSystem<SystemType>::runSystem()
    {
        const vector<Entity> &entities = this->getManagedEntities();

        try {
            this->run(entities);
        } catch (std::exception const &e) {
            std::cerr << "AbstractSystem::runSystem " << AbstractSystem<SystemType>::type.name() << " " << e.what()
                      << std::endl;
        }
    }

} // namespace Engine

#endif // ABSTRACTSYSTEM_HPP