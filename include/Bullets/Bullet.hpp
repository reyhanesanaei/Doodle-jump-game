#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f startPosition, bool facingRight);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    bool isOffScreen() const;

    bool isDestroyed() const;
    void destroy();
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;

    static constexpr float Speed = 700.f;

    bool m_destroyed = false;
};