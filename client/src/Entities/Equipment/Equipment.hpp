/*
** EPITECH PROJECT , 2021
** Equipment
** File description:
** \file Equipment.hpp
** \author simon
** \brief
** \date 14/11/2021
*/

#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include "Item/vector2D.hpp"
#include "GameCore/GameCore.hpp"

using Engine::ClusterName;

class Equipment {
  public:
    Equipment(ClusterName cluster, const vector2D &position);
    virtual ~Equipment() = default;

    void setNetworkId(uint32_t entityId);

    private:
        Engine::Entity _entity;
};

#endif // EQUIPEMENT_HPP
