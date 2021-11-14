/*
** EPITECH PROJECT , 2021
** EquipementComponent
** File description:
** \file EquipementComponent.hpp
** \author simon
** \brief
** \date 14/11/2021
*/

#ifndef EQUIPEMENTCOMPONENT_HPP
#define EQUIPEMENTCOMPONENT_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Engine {
    class EquipmentComponent : public BaseComponent<EquipmentComponent> {
      public:
        EquipmentComponent() = default;
        virtual ~EquipmentComponent() = default;

        size_t counter{0};
    };
}

#endif // EQUIPEMENTCOMPONENT_HPP
