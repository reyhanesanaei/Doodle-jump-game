#include "Platforms/Platform.hpp"

#include <utility>

Platform::Platform(const sf::Texture& texture, sf::Vector2f position)
    : m_sprite(texture)
{
    m_sprite.setPosition(position);
}

void Platform::update(float)
{
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);

    if(m_spring)
        m_spring->draw(window);
}

bool Platform::isSolid() const
{
    return true;
}

bool Platform::shouldRemove(float windowHeight) const
{
    return getY() > windowHeight + 60.f;
}

void Platform::move(float dy)
{
    m_sprite.move({0.f, dy});

    if(m_spring)
        m_spring->move(dy);
}

float Platform::getY() const
{
    return m_sprite.getPosition().y;
}

sf::FloatRect Platform::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Platform::attachSpring(std::unique_ptr<Spring> spring)
{
    m_spring = std::move(spring);
}

Spring* Platform::getSpring()
{
    return m_spring.get();
}

const Spring* Platform::getSpring() const
{
    return m_spring.get();
}
