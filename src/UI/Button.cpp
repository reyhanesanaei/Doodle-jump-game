#include "UI/Button.hpp"

Button::Button(const sf::Texture& texture)
    : m_sprite(texture)
{
}

void Button::setCenteredPosition(sf::Vector2f center, sf::Vector2f scale)
{
    m_sprite.setScale(scale);
    const auto bounds = m_sprite.getGlobalBounds();
    m_sprite.setPosition({
        center.x - bounds.size.x / 2.f,
        center.y - bounds.size.y / 2.f
    });
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

bool Button::contains(sf::Vector2i mousePosition) const
{
    return m_sprite.getGlobalBounds().contains({
        static_cast<float>(mousePosition.x),
        static_cast<float>(mousePosition.y)
    });
}
