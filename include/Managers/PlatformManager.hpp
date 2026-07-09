#pragma once

#include "Platforms/Platform.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <random>
#include <vector>

class PlatformManager
{
public:
    PlatformManager(
        const sf::Texture& normalTexture,
        const sf::Texture& movingTexture,
        const sf::Texture& breakableTexture,
        const sf::Texture& springTexture);

    void reset();
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void scroll(float dy);
    void removeOld(float windowHeight);
    void ensurePlatforms();

    std::vector<std::unique_ptr<Platform>>& platforms();
    const std::vector<std::unique_ptr<Platform>>& platforms() const;

private:
    void generateNextSafePlatform();
    void maybeGenerateBreakable(float nearY);
    void maybeAttachSpring(Platform& platform);
    bool overlapsExisting(const sf::FloatRect& bounds) const;

    float randomFloat(float min, float max);
    int randomInt(int min, int max);

    const sf::Texture& m_normalTexture;
    const sf::Texture& m_movingTexture;
    const sf::Texture& m_breakableTexture;
    const sf::Texture& m_springTexture;

    std::vector<std::unique_ptr<Platform>> m_platforms;
    std::mt19937 m_rng;
    float m_highestGeneratedY = 840.f;
    float m_lastSafeX = 270.f;
};
