#pragma once

#include "Entities/Player.hpp"
#include "Managers/PlatformManager.hpp"
#include "Platforms/Spring.hpp"

class CollisionManager
{
public:
    Platform* findLandedPlatform(Player& player, PlatformManager& platforms) const;
    Spring* findLandedSpring(Player& player, PlatformManager& platforms) const;

private:
    bool landsOnTop(const Player& player, const sf::FloatRect& targetBounds) const;
};
