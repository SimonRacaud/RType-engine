/*
** PERSONAL PROJECT, 2021
** TextManager
** File description:
** TextManager.cpp
*/

#include "TextManager.hpp"
#include "WindowManager/WindowManager.hpp"

TextManager::TextManager(): _pos(), _size(), _color(), _content(), _fontPath(), _font(nullptr), _text(nullptr)
{
}

TextManager::TextManager(const TextManager &src): _pos(src._pos), _size(src._size), _color(src._color), _content(src._content), _fontPath(src._fontPath), _font(src._font), _text(src._text)
{
}

TextManager::TextManager(vector2D pos, vector2D size, color_e color, std::string content, std::string path) : _pos(pos), _size(size), _color(color), _content(content), _fontPath(path), _font(nullptr), _text(nullptr)
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
    this->_color = color;
}

void TextManager::setSize(const vector2D &size)
{
    this->_size = size;
}

void TextManager::setPosition(const vector2D &pos)
{
    this->_pos = pos;
    if (_text)
        this->_text->setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
}

void TextManager::setContent(const std::string &str)
{
    this->_content = str;
    if (_text && _font)
        this->_text->setString(this->_content);
}

void TextManager::setFont(const std::string &name)
{
    this->_fontPath = name;
}

void TextManager::draw()
{
    if (!this->_text || !this->_font)
        this->refresh();
    WindowManager::_window->draw(*(this->_text.get()));
}

void TextManager::refresh()
{
    if (!this->_text)
        this->_text = std::make_shared<sf::Text>();
    if (!this->_font)
        this->_font = std::make_shared<sf::Font>();
    if (!this->_font->loadFromFile(this->_fontPath))
        throw std::invalid_argument("Invalid font " + this->_fontPath);
    this->_text->setFont(*(this->_font.get()));
    this->_text->setString(this->_content);
    this->_text->setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
    if (this->_size.x && this->_size.y)
        this->_text->setCharacterSize((this->_size.x + this->_size.y) * 8);
    try {
        this->_text->setFillColor(ColorLink::getColor(this->_color));
    } catch(...) {
        throw std::invalid_argument("Invalid color");
    }
}