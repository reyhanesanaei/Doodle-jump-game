#include "Platforms/NormalPlatform.hpp"

NormalPlatform::NormalPlatform(const sf::Texture& texture, sf::Vector2f position)
    : Platform(texture, position)
{
}

void NormalPlatform::onPlayerLanded(Player& player)
{
    player.jump();
}
