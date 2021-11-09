/*
** PERSONAL PROJECT, 2021
** TextManager
** File description:
** TextManager.hpp
*/

#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP

#include <unordered_map>
#include "build.hpp"
#include "Interface/ITextManager.hpp"

class TextManager: public ITextManager<renderToolSfml>
{
    public:
        TextManager();
        TextManager(const TextManager &);
        ~TextManager();

        const vector2D &getSize();
        const vector2D &getPosition();
        void setColor(const color_e &);
        void setSize(const vector2D &);
        void setPosition(const vector2D &);
        void setContent(const std::string &);
        void setFont(const std::string &);
        void draw(renderToolSfml &render);
        void refresh();

    private:
        vector2D _pos;
        vector2D _size;
        color_e _color;
        std::string _content;
        std::string _fontPath;
        std::shared_ptr<sf::Font> _font;
        std::shared_ptr<sf::Text> _text;
        const std::unordered_map<ITextManager::color_e, sf::Color> _colorLink = {
            {ITextManager::color_e::RED, sf::Color::Red},
            {ITextManager::color_e::BLUE, sf::Color::Blue},
            {ITextManager::color_e::GREEN, sf::Color::Green},
            {ITextManager::color_e::BLACK, sf::Color::Black},
            {ITextManager::color_e::WHITE, sf::Color::White},
        };
};

#endif