#include "Bullets/Bullet.hpp"

Bullet::Bullet(sf::Vector2f startPosition, bool facingRight)
{
    m_shape.setRadius(6.f);
    m_shape.setFillColor(sf::Color::Yellow);

    m_shape.setPosition(startPosition);

    m_velocity = {0.f, -Speed};
}

void Bullet::update(float dt)
{
    m_shape.move(m_velocity * dt);
}

void Bullet::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

bool Bullet::isOffScreen() const
{
    return m_shape.getPosition().y < -20.f;
}

sf::FloatRect Bullet::getBounds() const
{
    return m_shape.getGlobalBounds();
}

void Bullet::destroy()
{
    m_destroyed = true;
}

bool Bullet::isDestroyed() const
{
    return m_destroyed;
}