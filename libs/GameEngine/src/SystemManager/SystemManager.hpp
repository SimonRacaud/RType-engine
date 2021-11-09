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
#include <iostream>
#include "global.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Exception/InvalidParameterException.hpp"
#include "Exception/NotFoundException.hpp"
#include "IAbstractSystem.hpp"

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
         * @brief Returns a system of type from the list
         *
         * @tparam SystemType type to return
         * @return SystemType& returned reference
         */
        template <typename SystemType>
        SystemType &getSystem();

        /**
         * @brief For each system that is registered it calls its _onEntityUpdated
         * @brief DO NOT CALL OUTSIDE THE ENGINE, INTERNAL METHODE
         * @param entity
         * @param signature
         */
        void _onEntityUpdated(Entity entity, const Signature &signature);

        /**
         * @brief For each system that is registered it calls its _onEntityRemoved
         * @brief DO NOT CALL OUTSIDE THE ENGINE, INTERNAL METHODE
         * @param entity the Entity to remove
         */
        void _onEntityRemoved(Entity entity);

      private:
        template <class SystemType>
        void _checkType();

        std::vector<std::shared_ptr<IAbstractSystem>>::iterator retrieveSystem(const TypeIdx &type);
      private:
        std::vector<std::shared_ptr<IAbstractSystem>> _systems;
        std::vector<std::shared_ptr<IAbstractSystem>> _selectedSystems;
    };
}
namespace Engine {
    template <typename SystemType, typename... Args>
    SystemType &SystemManager::registerSystem(Args &&...systemArgs)
    {
        auto sys = this->retrieveSystem(SystemType::type);

        if (sys != _systems.end()) {
            std::cerr << "Did not create new system because it already exists" << std::endl;
            return *static_cast<SystemType *>(sys->get());
        }
        _systems.emplace_back(
            std::make_shared<SystemType>(std::forward<Args>(systemArgs)...)
                );
        return *static_cast<SystemType *>(_systems.back().get());
    }

    template <class SystemType>
    void SystemManager::unregisterSystem()
    {
        const TypeIdx type = SystemType::type;
        const auto it = std::find_if(_systems.begin(), _systems.end(),
            [type](std::shared_ptr<IAbstractSystem> &sysType) {
                return sysType->getType().hash_code() == type.hash_code();
        });
        const auto itSelect = std::find_if(_selectedSystems.begin(), _selectedSystems.end(),
            [type](std::shared_ptr<IAbstractSystem> &sysType) {
                return sysType->getType().hash_code() == type.hash_code();
        });

        if (it != _systems.end()) {
            _systems.erase(it);
        }
        if (itSelect != _selectedSystems.end()) {
            _selectedSystems.erase(itSelect);
        }
    }

    template <class... SystemTypeList>
    void SystemManager::selectSystems()
    {
        (this->selectSystem<SystemTypeList>(), ...);
    }

    template<class SystemType>
    void SystemManager::selectSystem()
    {
        auto it = retrieveSystem(SystemType::type);

        if (it == _systems.end())
            throw NotFoundException("Could not find system to select it");
        _selectedSystems.push_back((*it));
    }

    template <typename SystemType>
    SystemType &SystemManager::getSystem()
    {
        auto sys = retrieveSystem(SystemType::type);

        if (sys == _systems.end()) {
            throw InvalidParameterException(
                std::string("No registered system with type : "
                    + std::string(typeid(SystemType).name())));
        }
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