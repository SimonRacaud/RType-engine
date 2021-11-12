/*
** EPITECH PROJECT , 2021
** ImageView
** File description:
** \file ImageView.hpp
** \author simon
** \brief
** \date 12/11/2021
*/

#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP

#include <string>
#include "Item/vector2f.hpp"
#include "CustomCluster.hpp"
#include "Item/vector2D.hpp"

class ImageView {
  public:
    ImageView(
        const std::string &path,
        const vector2D &position,
        const vector2f &scale,
        Engine::ClusterName cluster
        );
    virtual ~ImageView() = default;
};

#endif // IMAGEVIEW_HPP
