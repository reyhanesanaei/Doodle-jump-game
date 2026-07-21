#include "Entities/Hole.hpp"

Hole::Hole(const sf::Texture& texture,
           sf::Vector2f position,
           HoleType type)
: m_sprite(texture)
, m_type(type)
{
    m_sprite.setPosition(position);
    m_sprite.setScale({0.8f,0.8f});
}

void Hole::update(float)
{
}

void Hole::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

void Hole::move(float dy)
{
    m_sprite.move({0.f, dy});
}

sf::FloatRect Hole::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

bool Hole::shouldRemove() const
{
    return m_sprite.getPosition().y > 1100.f;
}