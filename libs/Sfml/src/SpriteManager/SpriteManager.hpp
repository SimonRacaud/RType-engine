/*
** PERSONAL PROJECT, 2021
** SpriteManager
** File description:
** SpriteManager.hpp
*/

#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include "build.hpp"
#include "Interface/ISpriteManager.hpp"
#include "Item/vector2f.hpp"

class SpriteManager: public ISpriteManager
{
    public:
        SpriteManager();
        SpriteManager(vector2D pos, vector2f scale, std::string path);
        SpriteManager(const SpriteManager &);
        ~SpriteManager();

        const vector2f &getScale();
        const vector2D &getPosition();
        void setScale(const vector2f &scale);
        void setPosition(const vector2D &);
        void setSrcFilepath(const std::string &);
        void draw();
        void refresh();
        void setSize(const vector2D &);
        const vector2D &getSize();
    
    private:
        vector2D _pos;
        vector2f _size;
        std::string _path;
        std::shared_ptr<sf::Sprite> _sprite;
        std::shared_ptr<sf::Texture> _texture;
};

#endif