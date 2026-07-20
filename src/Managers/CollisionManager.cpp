#include "Managers/CollisionManager.hpp"

Platform* CollisionManager::findLandedPlatform(Player& player, PlatformManager& platforms) const
{
    for(auto& platform : platforms.platforms())
    {
        if(!platform->isSolid())
            continue;

        if(landsOnTop(player, platform->getBounds()))
            return platform.get();
    }

    return nullptr;
}

Spring* CollisionManager::findLandedSpring(Player& player, PlatformManager& platforms) const
{
    for(auto& platform : platforms.platforms())
    {
        Spring* spring = platform->getSpring();
        if(!spring || !spring->isActive())
            continue;

        if(landsOnTop(player, spring->getBounds()))
            return spring;
    }

    return nullptr;
}

bool CollisionManager::landsOnTop(const Player& player, const sf::FloatRect& targetBounds) const
{
    if(!player.isFalling())
        return false;

    const auto current = player.getBounds();
    const auto previous = player.getPreviousBounds();

    const float previousBottom = previous.position.y + previous.size.y;
    const float currentBottom = current.position.y + current.size.y;
    const float targetTop = targetBounds.position.y;

    const bool horizontallyOverlaps =
        current.position.x + current.size.x > targetBounds.position.x &&
        current.position.x < targetBounds.position.x + targetBounds.size.x;

    const bool crossesTop =
        previousBottom <= targetTop + 10.f &&
        currentBottom >= targetTop;

    return horizontallyOverlaps && crossesTop;
}
