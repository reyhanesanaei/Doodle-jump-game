#pragma once

#include <SFML/Graphics.hpp>

//phase2
enum class PlayerState
{
    Idle,
    Shooting
};
//

class Player
{
public:
Player(const sf::Texture& idleLeftTexture,
       const sf::Texture& idleRightTexture,
       //phase2
       const sf::Texture& shootingTexture,
       const sf::Texture& noseTexture
       //
    );

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

    //phase2
    PlayerState currentState = PlayerState::Idle;
    void setState(PlayerState state);

    sf::Vector2f getPosition() const;
    bool isFacingRight() const;
    //

private:
    void updateTexture();
    static constexpr float StartX = 278.f;
    static constexpr float StartY = 720.f;
    static constexpr float Speed = 320.f;
    static constexpr float Gravity = 1500.f;
    static constexpr float JumpVelocity = -820.f;
    static constexpr float SpringJumpVelocity = -1350.f;
    static constexpr float BreakableFallSpeed = 520.f;
    static constexpr float WindowWidth = 600.f;
    //phase2
    static constexpr float NoseOffsetRightX = 19.f;
    static constexpr float NoseOffsetLeftX  = 19.f;
    static constexpr float NoseOffsetY      = -1.f;
    //

    
    const sf::Texture& m_leftTexture;
    const sf::Texture& m_rightTexture;
    //phase2
    const sf::Texture& m_shooting_doodle;
    const sf::Texture& m_Nose;
    //

    sf::Sprite m_sprite;
    sf::Sprite m_noseSprite; //phase2
    sf::Vector2f m_velocity{0.f, 0.f};
    sf::Vector2f m_previousPosition{StartX, StartY};
    bool m_facingRight = false;
};
