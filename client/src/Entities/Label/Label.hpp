/*
** EPITECH PROJECT , 2021
** Label
** File description:
** \file Label.hpp
** \author simon
** \brief
** \date 12/11/2021
*/

#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>
#include "Item/vector2D.hpp"
#include "ColorLink/ColorLink.hpp"
#include "CustomCluster.hpp"

using std::string;

class Label {
  public:
    Label(Engine::ClusterName cluster, string const& content,
        vector2D const& position, vector2D const& size, color_e color);

    Label(Engine::ClusterName cluster, size_t content,
        vector2D const& position, vector2D const& size, color_e color);
    virtual ~Label() = default;
};

#endif // LABEL_HPP
