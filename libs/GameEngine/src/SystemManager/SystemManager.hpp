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

namespace Engine
{
    class SystemManager {
      public:
        SystemManager() = default;
        ~SystemManager() = default;

        template <class SystemType, typename... Args>
        SystemType &registerSystem(Args &&...args);

        template <class SystemType>
        void unregisterSystem();

        template <typename... Args>
        void select();

        void executeCycle();

        void onEntityUpdated(Entity entity, const Signature &signature);
        void onEntityRemoved(Entity entity);

        template <typename SystemType>
        SystemType &getSystem();

      private:
        template <class SystemType>
        void _checkType();

      private:
        std::vector<std::shared_ptr<IAbstractSystem>> _systems;
        std::vector<std::shared_ptr<IAbstractSystem>> _selector;
    };
}

#include "AbstractSystem/AbstractSystem.hpp"

namespace Engine {
    template <typename SystemType, typename... Args>
    SystemType &SystemManager::registerSystem(Args &&...args)
    {
        // TODO
//        const std::type_info &type = typeid(SystemType);
//
//        if (std::find_if(_types.begin(), _types.end(),
//                [&type](auto &sysType) {
//                    return sysType.get() == type;
//                })
//            != _types.end()) {
//            throw std::exception();
//        }
//        auto &system = _systems.emplace_back(std::make_unique<SystemType>(std::forward<Args>(args)...));
//        _types.emplace_back(typeid(SystemType));
//        return static_cast<SystemType *>(system.get());
    }

    template <class SystemType>
    void SystemManager::unregisterSystem()
    {
        // TODO
    }

    template <typename... Args>
    void SystemManager::select()
    {
        // TODO
    }

    template <typename SystemType>
    SystemType &SystemManager::getSystem()
    {
        // TODO
//        std::size_t index = 0;
//        const std::type_info &type = typeid(SystemType);
//        auto type_it = std::find_if(_types.begin(), _types.end(), [&](auto &sysType) {
//            return sysType.get() == type;
//        });
//
//        if (type_it == _types.end()) {
//            throw std::invalid_argument("Invalid system type (not registered?)");
//        }
//        index = std::distance(_types.begin(), type_it);
//        return *(static_cast<SystemType *>(_systems[index].get()));
    }

    template <class SystemType>
    void SystemManager::_checkType()
    {
        static_assert(std::is_base_of<AbstractSystem<SystemType>, SystemType>::value,
            "Invalid system type");
    }

} // namespace Engine

#endif // SYSTEMMANAGER_HPP