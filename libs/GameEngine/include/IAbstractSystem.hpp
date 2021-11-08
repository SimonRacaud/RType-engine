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

namespace Engine {
    class IAbstractSystem {
      public:
        virtual ~IAbstractSystem() = default;

        virtual SystemPriority getPriority() const = 0;
        virtual TypeIdx getType() const = 0;

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
        virtual const std::vector<Entity> &getManagedEntities() const = 0;
    };

}

#endif // IABSTRACTSYSTEL_HPP
