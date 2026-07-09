#include "Platforms/Spring.hpp"

Spring::Spring(const sf::Texture& texture, sf::Vector2f position)
    : m_sprite(texture)
{
    m_sprite.setPosition(position);
}

void Spring::draw(sf::RenderWindow& window) const
{
    if(m_active)
        window.draw(m_sprite);
}

void Spring::move(float dy)
{
    m_sprite.move({0.f, dy});
}

sf::FloatRect Spring::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

bool Spring::isActive() const
{
    return m_active;
}

void Spring::deactivate()
{
    m_active = false;
}
