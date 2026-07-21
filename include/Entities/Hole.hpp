#pragma once

#include <SFML/Graphics.hpp>

enum class HoleType
{
    Small,
    Large
};

class Hole
{
public:
    Hole(const sf::Texture& texture,
         sf::Vector2f position,
         HoleType type);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    void move(float dy);

    sf::FloatRect getBounds() const;

    bool shouldRemove() const;

private:
    sf::Sprite m_sprite;
    HoleType m_type;
};