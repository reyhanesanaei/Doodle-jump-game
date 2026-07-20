#include "Platforms/BreakablePlatform.hpp"

BreakablePlatform::BreakablePlatform(const sf::Texture& texture, sf::Vector2f position)
    : Platform(texture, position)
{
}

void BreakablePlatform::update(float dt)
{
    if(m_broken)
        m_sprite.move({0.f, m_fallSpeed * dt});
}

void BreakablePlatform::onPlayerLanded(Player& player)
{
    if(!m_broken)
    {
        m_broken = true;
        player.beginBreakableFall();
    }
}

bool BreakablePlatform::isSolid() const
{
    return !m_broken;
}

bool BreakablePlatform::shouldRemove(float windowHeight) const
{
    return getY() > windowHeight + 60.f;
}
