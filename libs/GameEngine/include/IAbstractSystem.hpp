/*
** EPITECH PROJECT , 2021
** IAbstractSystem
** File description:
** \file IAbstractSystem.hpp
** \author simon
** \brief
** \date 01/11/2021
*/

#ifndef IABSTRACTSYSTEM_HPP
#define IABSTRACTSYSTEM_HPP

#include "SystemPriority.hpp"
#include "global.hpp"

namespace Engine
{
    class IAbstractSystem {
      public:
        virtual ~IAbstractSystem() = default;

        [[nodiscard]] virtual SystemPriority getPriority() const = 0;
        [[nodiscard]] virtual TypeIdx getType() const = 0;

        /**
         * \brief Execute the logic of the class
         */
        virtual void run(const std::vector<Entity> &entities) = 0;

        /**
         * \brief technical operations before run(), do not override
         */
        virtual void runSystem() = 0;

        /**
         * \brief Do the system need to be executed? (running frequency)
         */
        virtual bool refresh() = 0;

        virtual void onEntityUpdated(Entity entity, const Signature &components) = 0;
        virtual void onEntityRemoved(Entity entity) = 0;

      protected:
        [[nodiscard]] virtual const std::vector<Entity> &getManagedEntities() const = 0;
    };

} // namespace Engine

#endif // IABSTRACTSYSTEL_HPP