#pragma once

#include "Platforms/Platform.hpp"

class BreakablePlatform : public Platform
{
public:
    BreakablePlatform(const sf::Texture& texture, sf::Vector2f position);

    void update(float dt) override;
    void onPlayerLanded(Player& player) override;
    bool isSolid() const override;
    bool shouldRemove(float windowHeight) const override;

private:
    bool m_broken = false;
    float m_fallSpeed = 520.f;
};
