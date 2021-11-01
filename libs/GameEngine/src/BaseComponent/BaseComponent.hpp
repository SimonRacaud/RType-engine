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
    template <class ComponentType> class BaseComponent {
        friend class ComponentManager;

      public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        /**
         * \brief unique id of the component
         */
        static const TypeIdx type;

        static Index getIndex();

      private:
        static void setIndex(Index index);
        static Index idx;
    };

    template <class ComponentType>
    Index BaseComponent<ComponentType>::getIndex()
    {
        if (BaseComponent<ComponentType>::idx == InvalidIndex) {
            throw NotRegisteredException("Component");
        }
        return BaseComponent<ComponentType>::idx;
    }
    template <class ComponentType>
    void BaseComponent<ComponentType>::setIndex(Index index)
    {
        BaseComponent<ComponentType>::idx = index;
    }

    template <typename ComponentType>
    const TypeIdx BaseComponent<ComponentType>::type = GET_TYPE_IDX(BaseComponent<ComponentType>);

    template <typename ComponentType>
    Index BaseComponent<ComponentType>::idx = InvalidIndex;

} // namespace Engine

#endif // BASE_COMPONENT_HPP