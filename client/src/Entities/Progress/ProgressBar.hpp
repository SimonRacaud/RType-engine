/*
** EPITECH PROJECT , 2021
** ProgressBar
** File description:
** \file ProgressBar.hpp
** \author simon
** \brief
** \date 13/11/2021
*/

#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "Item/vector2D.hpp"
#include "ColorLink/ColorLink.hpp"
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"

using Engine::ClusterName;
using Engine::EntityName;

class ProgressBar {
  public:
    ProgressBar(ClusterName cluster, EntityName name, const vector2D &position,
        const vector2D &size, color_e primaryColor, color_e backgroundColor);
    virtual ~ProgressBar() = default;
};

#endif // PROGRESSBAR_HPP
