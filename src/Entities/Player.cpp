#include "Entities/Player.hpp"

#include <algorithm>

Player::Player(const sf::Texture& leftTexture, 
                const sf::Texture& rightTexture,
                const sf::Texture& shootLeftTexture,
                const sf::Texture& shootRightTexture)
            : m_leftTexture(leftTexture),
            m_rightTexture(rightTexture),
            m_shooting_doodle(shootLeftTexture),
            m_Nose(shootRightTexture),
            m_sprite(m_leftTexture),
            m_noseSprite(m_Nose)
{
    reset();
}

void Player::update(float dt)
{
    m_previousPosition = m_sprite.getPosition();
    m_velocity.x = 0.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (m_facingRight)
        {
            m_facingRight = false;
            updateTexture();
        }
        m_velocity.x = -Speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if(!m_facingRight)
        {
            m_facingRight = true;
            updateTexture();
        }
        m_velocity.x = Speed;
    }

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
{
    if (currentState != PlayerState::Shooting)
    {
        setState(PlayerState::Shooting);
        updateTexture();
    }
}
else
{
    if (currentState != PlayerState::Idle)
    {
        setState(PlayerState::Idle);
        updateTexture();
    }
}
    m_velocity.y += Gravity * dt;
    m_sprite.move(m_velocity * dt);

    //phase2
    const auto bodyPos = m_sprite.getPosition();

    if (m_facingRight)
    {
        m_noseSprite.setPosition({
            bodyPos.x + NoseOffsetRightX,
            bodyPos.y + NoseOffsetY
        });
    }
    else
    {
        m_noseSprite.setPosition({
            bodyPos.x + NoseOffsetLeftX,
            bodyPos.y + NoseOffsetY
        });
    }
    //

    const auto bounds = m_sprite.getGlobalBounds();
    if(bounds.position.x + bounds.size.x < 0.f)
        m_sprite.setPosition({WindowWidth, m_sprite.getPosition().y});
    else if(bounds.position.x > WindowWidth)
        m_sprite.setPosition({-bounds.size.x, m_sprite.getPosition().y});

}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);

    //phase2
    if (currentState == PlayerState::Shooting)
    {
        window.draw(m_noseSprite);
    }
    //
}

void Player::reset()
{
    m_velocity = {0.f, 0.f};
    m_previousPosition = {StartX, StartY};
    m_facingRight = false;
    currentState = PlayerState::Idle;
    updateTexture();
    m_sprite.setScale({0.45f, 0.45f});
    m_noseSprite.setScale({0.6f , 0.6f}); //phase2
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

//phase2

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

bool Player::isFacingRight() const
{
    return m_facingRight;
}

void Player::setState(PlayerState state)
{
    currentState = state;
}


//phase2
void Player::updateTexture()
{
    if (currentState == PlayerState::Idle)
    {
        if (m_facingRight)
            m_sprite.setTexture(m_rightTexture, true);
        else
            m_sprite.setTexture(m_leftTexture, true);
    }
    else // Shooting
    {
        m_sprite.setTexture(m_shooting_doodle, true);
    }

    if (currentState == PlayerState::Idle)
    {
        m_sprite.setScale({0.45f, 0.45f});
    }
    else
    {
        m_sprite.setScale({0.90f, 0.90f});
    }
}
//