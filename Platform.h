#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
private:
    sf::Texture normalPlatform;
    sf::Sprite sprite;

public:
    Platform(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};