/*
** EPITECH PROJECT , 2021
** EntityLinkComponent
** File description:
** \file EntityLinkComponent.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef ENTITYLINKCOMPONENT_HPP
#define ENTITYLINKCOMPONENT_HPP

#include "BaseComponent/BaseComponent.hpp"
#include "global.hpp"
#include <unordered_map>
#include <string>

namespace Engine {
    using std::unordered_map;

    struct EntityLinkComponent {
        EntityLinkComponent() = default;
        virtual ~EntityLinkComponent() = default;

        unordered_map<string, Entity> values;
    };
}

#endif // ENTITYLINKCOMPONENT_HPP
