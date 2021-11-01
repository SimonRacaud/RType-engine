/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
**
*/

#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP

#include <cstddef>
#include <typeindex>
#include <typeinfo>

namespace Engine
{
    template <class ComponentType> class BaseComponent {
      public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        /**
         * \brief unique id of the component
         */
        static const std::type_index type;
    };

    template <typename ComponentType>
    const std::type_index BaseComponent<ComponentType>::type = \
        std::type_index(typeid(BaseComponent<ComponentType>));

} // namespace Engine

#endif // BASE_COMPONENT_HPP