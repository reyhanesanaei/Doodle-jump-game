#pragma once

#include <SFML/Graphics.hpp>

class Spring
{
public:
    Spring(const sf::Texture& texture, sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;
    void move(float dy);

    sf::FloatRect getBounds() const;
    bool isActive() const;
    void deactivate();

private:
    sf::Sprite m_sprite;
    bool m_active = true;
};
