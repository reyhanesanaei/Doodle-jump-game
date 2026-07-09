#include "Entities/Player.hpp"

#include <algorithm>

Player::Player(const sf::Texture& leftTexture, const sf::Texture& rightTexture)
    : m_leftTexture(leftTexture),
      m_rightTexture(rightTexture),
      m_sprite(m_leftTexture)
{
    reset();
}

void Player::update(float dt)
{
    m_previousPosition = m_sprite.getPosition();
    m_velocity.x = 0.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if(m_facingRight)
        {
            m_sprite.setTexture(m_leftTexture, true);
            m_sprite.setScale({0.45f, 0.45f});
            m_facingRight = false;
        }
        m_velocity.x = -Speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if(!m_facingRight)
        {
            m_sprite.setTexture(m_rightTexture, true);
            m_sprite.setScale({0.45f, 0.45f});
            m_facingRight = true;
        }
        m_velocity.x = Speed;
    }

    m_velocity.y += Gravity * dt;
    m_sprite.move(m_velocity * dt);

    const auto bounds = m_sprite.getGlobalBounds();
    if(bounds.position.x + bounds.size.x < 0.f)
        m_sprite.setPosition({WindowWidth, m_sprite.getPosition().y});
    else if(bounds.position.x > WindowWidth)
        m_sprite.setPosition({-bounds.size.x, m_sprite.getPosition().y});
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

void Player::reset()
{
    m_velocity = {0.f, 0.f};
    m_previousPosition = {StartX, StartY};
    m_facingRight = false;
    m_sprite.setTexture(m_leftTexture, true);
    m_sprite.setScale({0.45f, 0.45f});
    m_sprite.setPosition({StartX, StartY});
}

void Player::jump()
{
    m_velocity.y = JumpVelocity;
}

void Player::springJump()
{
    m_velocity.y = SpringJumpVelocity;
}

void Player::beginBreakableFall()
{
    m_velocity.y = std::max(m_velocity.y, BreakableFallSpeed);
}

void Player::move(float dy)
{
    m_sprite.move({0.f, dy});
    m_previousPosition.y += dy;
}

bool Player::isFalling() const
{
    return m_velocity.y > 0.f;
}

float Player::getY() const
{
    return m_sprite.getPosition().y;
}

sf::FloatRect Player::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

sf::FloatRect Player::getPreviousBounds() const
{
    return sf::FloatRect(m_previousPosition, getBounds().size);
}
