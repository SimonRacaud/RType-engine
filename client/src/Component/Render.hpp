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
        Render(DrawableObj src) : _pos({0}), _src({src}) {}
        Render(std::vector<DrawableObj> &src, const std::vector<size_t> &pos = {}) : _pos(pos), _src(std::move(src)) {}
        Render() = delete;
        virtual ~Render() = default;

        void setRender(size_t pos)
        {
            if (pos < _src.size())
                _pos.push_back(pos);
        }

        void removeRender(size_t pos)
        {
            std::remove(this->_pos.begin(), this->_pos.end(), pos);
        }

        std::vector<size_t> _pos;
        std::vector<DrawableObj> _src;
    };
}

#endif