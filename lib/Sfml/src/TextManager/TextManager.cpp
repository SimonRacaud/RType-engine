/*
** PERSONAL PROJECT, 2021
** TextManager
** File description:
** TextManager.cpp
*/

#include "TextManager.hpp"

TextManager::TextManager(): _pos(), _size(), _color(), _content(), _fontPath(), _font(nullptr), _text(nullptr)
{
}

TextManager::TextManager(const TextManager &src): _pos(src._pos), _size(src._size), _color(src._color), _content(src._content), _fontPath(src._fontPath), _font(src._font), _text(src._text)
{
}

TextManager::~TextManager()
{
    if (this->_font)
        this->_font.reset();
    if (this->_text)
        this->_text.reset();
}

const vector2D &TextManager::getSize()
{
    return this->_size;
}

const vector2D &TextManager::getPosition()
{
    return this->_pos;
}

void TextManager::setColor(const color_e &color)
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    try {
        this->_text->setFillColor(this->_colorLink.at(color));
    } catch(...) {
        throw std::invalid_argument("Invalid color");
    }
}

void TextManager::setSize(const vector2D &size)
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    this->_text->setCharacterSize((size.x + size.y) / 2);
    this->_size = size;
}

void TextManager::setPosition(const vector2D &pos)
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    this->_text->setPosition(sf::Vector2f(pos.x, pos.y));
    this->_pos = pos;
}

void TextManager::setContent(const std::string &str)
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    this->_text->setString(str);
}

void TextManager::setFont(const std::string &name)
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    if (!this->_font)
        this->_font = std::make_shared<sf::Font>();
    if (!this->_font->loadFromFile(name))
        throw std::invalid_argument("Invalid font " + name);
    this->_text->setFont(*(this->_font.get()));
}

void TextManager::draw(renderToolSfml &render)
{
    if (!this->_text || !this->_font)
        throw std::invalid_argument("Text and Font must be init");
    render->draw(*(this->_text.get()));
}

void TextManager::refresh()
{
    // TODO UNUSED
}