#include "Platforms/MovingPlatform.hpp"

MovingPlatform::MovingPlatform(const sf::Texture& texture, sf::Vector2f position)
    : Platform(texture, position)
{
}

void MovingPlatform::update(float dt)
{
    const float direction = m_movingRight ? 1.f : -1.f;
    m_sprite.move({m_speed * direction * dt, 0.f});

    const auto bounds = getBounds();
    if(bounds.position.x <= 0.f)
        m_movingRight = true;
    else if(bounds.position.x + bounds.size.x >= 600.f)
        m_movingRight = false;
}

void MovingPlatform::onPlayerLanded(Player& player)
{
    player.jump();
}
