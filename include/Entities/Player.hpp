#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(const sf::Texture& leftTexture, const sf::Texture& rightTexture);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void reset();

    void jump();
    void springJump();
    void beginBreakableFall();
    void move(float dy);

    bool isFalling() const;
    float getY() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getPreviousBounds() const;

private:
    static constexpr float StartX = 278.f;
    static constexpr float StartY = 720.f;
    static constexpr float Speed = 320.f;
    static constexpr float Gravity = 1500.f;
    static constexpr float JumpVelocity = -820.f;
    static constexpr float SpringJumpVelocity = -1350.f;
    static constexpr float BreakableFallSpeed = 520.f;
    static constexpr float WindowWidth = 600.f;

    const sf::Texture& m_leftTexture;
    const sf::Texture& m_rightTexture;
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity{0.f, 0.f};
    sf::Vector2f m_previousPosition{StartX, StartY};
    bool m_facingRight = false;
};
