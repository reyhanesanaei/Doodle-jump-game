#pragma once

#include "Platforms/Platform.hpp"

class MovingPlatform : public Platform
{
public:
    MovingPlatform(const sf::Texture& texture, sf::Vector2f position);

    void update(float dt) override;
    void onPlayerLanded(Player& player) override;

private:
    float m_speed = 135.f;
    bool m_movingRight = true;
};
