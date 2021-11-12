/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
**
*/

#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP

#include "Exception/NotRegisteredException.hpp"
#include <cstddef>
#include <typeindex>
#include <typeinfo>

#include "global.hpp"

namespace Engine
{
    /**
     * \brief Every components must inherit of BaseComponent
     * @tparam ComponentType
     */
    template <class ComponentType> class BaseComponent {
        /**
         * \brief The component manager is the only one that can do setIndex.
         */
        friend class ComponentManager;

      public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        /**
         * \brief Unique id of the component type.
         */
        static const TypeIdx type;

        /**
         * @throws NotRegisteredException
         * @return
         */
        static Index getIndex();
      private:
        static void setIndex(Index index);

      private:
        /**
         * \brief Index of the component type in the register list. (ECS)
         */
        static Index _index;
    };

    template <class ComponentType>
    Index BaseComponent<ComponentType>::getIndex()
    {
        if (BaseComponent<ComponentType>::_index == InvalidIndex) {
            throw NotRegisteredException("Component not registered");
        }
        return BaseComponent<ComponentType>::_index;
    }
    template <class ComponentType>
    void BaseComponent<ComponentType>::setIndex(Index index)
    {
        BaseComponent<ComponentType>::_index = index;
    }

    template <typename ComponentType>
    const TypeIdx BaseComponent<ComponentType>::type = GET_TYPE_IDX(BaseComponent<ComponentType>);

    template <typename ComponentType>
    Index BaseComponent<ComponentType>::_index = InvalidIndex;

} // namespace Engine

#endif // BASE_COMPONENT_HPP