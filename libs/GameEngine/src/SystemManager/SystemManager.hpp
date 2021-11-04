/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 31/05/2021 SystemManager.hpp.h
*/

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory>
#include <typeinfo>
#include <vector>
#include "global.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Exception/InvalidParameterException.hpp"
#include "Exception/NotFoundException.hpp"

namespace Engine
{
    using std::vector;
    using std::shared_ptr;

    class SystemManager {
      public:
        SystemManager() = default;
        ~SystemManager() = default;

        /**
         * @brief Creates and adds a system to the systems vector
         *
         * @tparam SystemType  the type of the system to create
         * @tparam Args
         * @param systemArgs  the arguments to send to the system
         * @return SystemType& a reference to the newly created system
         */
        template <class SystemType, typename... Args>
        SystemType &registerSystem(Args &&...args);

        /**
         * @brief Removes a system from the vector
         *
         * @tparam SystemType the type of the system to remove
         */
        template <class SystemType>
        void unregisterSystem();

        /**
         * @brief Selects a list of systems to add them to the selected vector
         *
         * @tparam Args
         * @param systemTypeList All of the systems to select
         */
        template <class SystemTypeList>
        void selectSystem();

        template<class... SystemTypeList>
        void selectSystems();

        /**
         * @brief Executes every selected system
         *
         */
        void executeCycle();

        /**
         * @brief For each system that is registered it calls its onEntityUpdated
         *
         * @param entity
         * @param signature
         */
        void onEntityUpdated(Entity entity, const Signature &signature);

        /**
         * @brief For each system that is registered it calls its onEntityRemoved
         *
         * @param entity the Entity to remove
         */
        void onEntityRemoved(Entity entity);


        /**
         * @brief Returns a system of type from the list
         *
         * @tparam SystemType type to return
         * @return SystemType& returned reference
         */
        template <typename SystemType>
        SystemType &getSystem();

      private:
        template <class SystemType>
        void _checkType();

        std::vector<std::shared_ptr<IAbstractSystem>>::iterator retrieveSystem(const TypeIdx &type);
      private:
        std::vector<std::shared_ptr<IAbstractSystem>> _systems;
        std::vector<std::shared_ptr<IAbstractSystem>> _selectedSystems;
    };
}

#include "AbstractSystem/AbstractSystem.hpp"

namespace Engine {
    template <typename SystemType, typename... Args>
    SystemType &SystemManager::registerSystem(Args &&...systemArgs)
    {
        auto sys = retrieveSystem(GET_TYPE_IDX(SystemType));

        if (sys != _systems.end()) {
            std::cerr << "Did not create new system because it already exists" << std::endl;
            return *static_cast<SystemType *>(sys->get());
        }
        shared_ptr<IAbstractSystem> newSys = _systems.emplace_back(std::make_unique<SystemType>(std::forward<Args>(systemArgs)...));
        return *static_cast<SystemType *>(newSys.get());
    }

    template <class SystemType>
    void SystemManager::unregisterSystem()
    {
        const TypeIdx type = std::type_index(typeid(SystemType));

        _systems.erase(std::remove_if(_systems.begin(), _systems.end(), [&](auto &sysType) {
            return sysType.getType() == type;
        }));
    }

    template <class... SystemTypeList>
    void SystemManager::selectSystems()
    {
        (this->selectSystems<SystemTypeList>(), ...);
    }

    template<class SystemType>
    void SystemManager::selectSystem()
    {
        auto it = retrieveSystem(GET_TYPE_IDX(SystemType));

        if (it == _systems.end())
            throw NotFoundException("Could not find system to select it");
        _selectedSystems.push_back(*it);
    }

    template <typename SystemType>
    SystemType &SystemManager::getSystem()
    {
        auto sys = retrieveSystem(GET_TYPE_IDX(SystemType));

        if (sys == _systems.end())
            throw InvalidParameterException(std::string("No registered system with type : " + std::string(typeid(SystemType).name())));
        return *sys;
    }

    template <class SystemType>
    void SystemManager::_checkType()
    {
        static_assert(std::is_base_of<AbstractSystem<SystemType>, SystemType>::value,
            "Invalid system type");
    }

} // namespace Engine

#endif // SYSTEMMANAGER_HPP