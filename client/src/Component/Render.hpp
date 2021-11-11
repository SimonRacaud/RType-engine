/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 Render.hpp.h
*/

#ifndef RENDER_HPP
#define RENDER_HPP

#include "build.hpp"
#include "Interface/IDrawable.hpp"
#include "BaseComponent/BaseComponent.hpp"

namespace Engine
{
    using DrawableObj = std::shared_ptr<IDrawable<renderToolSfml>>;
    struct Render : public BaseComponent<Render> {
        Render(DrawableObj src) : _src(src) {}
        Render() = delete;
        virtual ~Render() = default;

        DrawableObj _src;
    };
}

#endif