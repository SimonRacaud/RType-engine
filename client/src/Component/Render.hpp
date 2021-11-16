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
    using DrawableObj = std::shared_ptr<IDrawable>;
    struct Render : public BaseComponent<Render> {
        Render(DrawableObj src) : _pos({0}), _src({src}) {}
        Render(std::vector<DrawableObj> &src, const std::vector<size_t> &pos = {}) : _pos({}), _src(std::move(src))
        {
            for (auto &it : pos)
                this->setRender(it);
        }
        Render() = delete;
        virtual ~Render() = default;

        void replaceLastRender(size_t newV)
        {
            this->_pos[this->_pos.size() - 1] = newV;
        }

        void replaceRender(size_t old, size_t newV)
        {
            std::replace(this->_pos.begin(), this->_pos.end(), old, newV);
        }

        void setRender(size_t pos)
        {
            if (pos < _src.size())
                _pos.push_back(pos);
        }

        void removeRender(size_t pos)
        {
            for (size_t i = 0; i < _pos.size(); i++)
                if (_pos[i] == pos)
                    _pos.erase(_pos.begin() + i);
        }

        std::vector<size_t> _pos;
        std::vector<DrawableObj> _src;
    };
}

#endif