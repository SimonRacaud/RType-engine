/*
** PERSONAL PROJECT, 2021
** AnimationManager
** File description:
** AnimationManager.hpp
*/

#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "build.hpp"
#include "FrameRateLimiter.hpp"
#include "Interface/IAnimationManager.hpp"

class AnimationManager: public IAnimationManager<renderToolSfml>
{
    public:
        AnimationManager();
        AnimationManager(const AnimationManager &);
        ~AnimationManager();

        const vector2D &getSize();
        const vector2D &getPosition();
        void setSize(const vector2D &);
        void setPosition(const vector2D &);
        void setSrcPath(const std::string &);
        void draw(renderToolSfml &render);
        void refresh();
        void setNbMember(size_t);
        void forceOffset(size_t);
        void setFocus(const surface &);

    private:
        void nextStep();
        const sf::Drawable &getNextSprite();
        static void stepManager(size_t &);

    private:
        vector2D _pos;
        vector2D _size;
        std::string _path;
        std::shared_ptr<sf::Sprite> _sprite;
        std::shared_ptr<sf::Texture> _texture;
        size_t _offset;
        surface _focus;
        size_t _nb;
        Singly::FrameRateLimiter<void (size_t &)> _limiter;
};

#endif