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

class SpriteManager: public ISpriteManager<renderToolSfml>
{
    public:
        SpriteManager();
        SpriteManager(vector2D pos, vector2D size, std::string path);
        SpriteManager(const SpriteManager &);
        ~SpriteManager();

        const vector2D &getSize();
        const vector2D &getPosition();
        void setSize(const vector2D &);
        void setPosition(const vector2D &);
        void setSrcFilepath(const std::string &);
        void draw(renderToolSfml &render);
        void refresh();
    
    private:
        vector2D _pos;
        vector2D _size;
        std::string _path;
        std::shared_ptr<sf::Sprite> _sprite;
        std::shared_ptr<sf::Texture> _texture;
};

#endif