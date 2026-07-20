#include "Entities/Monster.hpp"

Monster::Monster(const sf::Texture& texture,
                 sf::Vector2f position,
                 MonsterType type)
    : m_sprite(texture),
      m_type(type)
{
    m_sprite.setPosition(position);
    m_sprite.setScale({0.8f, 0.8f});

    m_health = (m_type == MonsterType::Blue) ? 1 : 3;
    m_speed = (m_type == MonsterType::Blue) ? 90.f : 120.f;
    m_alive = m_health > 0;

    if (m_type == MonsterType::Blue)
    {
        auto size = texture.getSize();

        m_sprite.setTextureRect({
            {0, 0},
            {static_cast<int>(size.x / 2),
            static_cast<int>(size.y)}
        });
    }

    m_velocity = {50.f, 0.f};
}

void Monster::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

sf::FloatRect Monster::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

MonsterType Monster::getType() const
{
    return m_type;
}

void Monster::takeDamage()
{
    if (!m_alive)
        return;

    --m_health;
    if (m_health <= 0)
        m_alive = false;
}

bool Monster::isAlive() const
{
    return m_alive;
}

void Monster::update(float dt)
{
    if (m_moveRight)
        m_sprite.move({m_speed * dt, 0.f});
    else
        m_sprite.move({-m_speed * dt, 0.f});

    if (m_sprite.getPosition().x < 0.f)
        m_moveRight = true;

    if (m_sprite.getPosition().x > 520.f)
        m_moveRight = false;

    m_sprite.move(m_velocity * dt);

    auto bounds = m_sprite.getGlobalBounds();

    if (bounds.position.x <= 0.f)
    {
        m_velocity.x = std::abs(m_velocity.x);
        m_facingRight = true;
    }

    if (bounds.position.x + bounds.size.x >= 600.f)
    {
        m_velocity.x = -std::abs(m_velocity.x);
        m_facingRight = false;
    }

    auto texSize = m_sprite.getTexture().getSize();

if (m_type == MonsterType::Blue)
{
    auto texSize = m_sprite.getTexture().getSize();

        if (m_facingRight)
        {
            m_sprite.setTextureRect({
                {static_cast<int>(texSize.x / 2), 0},
                {static_cast<int>(texSize.x / 2),
                static_cast<int>(texSize.y)}
            });
        }
        else
        {
            m_sprite.setTextureRect({
                {0,0},
                {static_cast<int>(texSize.x / 2),
                static_cast<int>(texSize.y)}
            });
        }
    }
}

void Monster::move(float dy)
{
    m_sprite.move({0.f, dy});
}

bool Monster::isDead() const
{
    return !m_alive;
}