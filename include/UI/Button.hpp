#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
    explicit Button(const sf::Texture& texture);

    void setCenteredPosition(sf::Vector2f center, sf::Vector2f scale = {1.f, 1.f});
    void draw(sf::RenderWindow& window) const;
    bool contains(sf::Vector2i mousePosition) const;

private:
    sf::Sprite m_sprite;
};
