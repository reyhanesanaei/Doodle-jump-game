#pragma once

#include <SFML/Graphics.hpp>

enum class MonsterType
{
    Blue,
    Green
};

class Monster
{
public:
    Monster(const sf::Texture& texture,
            sf::Vector2f position,
            MonsterType type);

    void update(float dt);
    void move(float dy);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    MonsterType getType() const;

    void takeDamage();
    bool isAlive() const;
    bool isDead() const;
    bool m_facingRight = true;

private:

    sf::Sprite m_sprite;

    float m_speed = 120.f;
    bool m_moveRight = true;

    MonsterType m_type;
    int m_health;
    bool m_alive = true;


    sf::Vector2f m_velocity;
};