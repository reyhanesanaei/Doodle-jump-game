#include "Managers/PlatformManager.hpp"

#include "Platforms/BreakablePlatform.hpp"
#include "Platforms/MovingPlatform.hpp"
#include "Platforms/NormalPlatform.hpp"

#include <algorithm>
#include <chrono>

namespace
{
    constexpr float InitialPlatformY = 840.f;
    constexpr float TopGenerationLimit = -180.f;
    constexpr float MinX = 25.f;
    constexpr float MaxX = 515.f;
    constexpr float MaxHorizontalGap = 220.f;
}

PlatformManager::PlatformManager(
    const sf::Texture& normalTexture,
    const sf::Texture& movingTexture,
    const sf::Texture& breakableTexture,
    const sf::Texture& springTexture)
    : m_normalTexture(normalTexture),
      m_movingTexture(movingTexture),
      m_breakableTexture(breakableTexture),
      m_springTexture(springTexture),
      m_rng(static_cast<unsigned>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count()))
{
    reset();
}

//Starting over
void PlatformManager::reset()
{
    //removing all platforms and resetting the highest generated Y and last safe X
    m_platforms.clear();
    m_highestGeneratedY = InitialPlatformY;
    m_lastSafeX = 270.f;

    //deciding to start with a normal platform at the initial position
    m_platforms.push_back(std::make_unique<NormalPlatform>(
        m_normalTexture,
        sf::Vector2f{m_lastSafeX, m_highestGeneratedY}));
    //this loop ensures that platforms are generated until the highest generated Y is above the top generation limit, effectively filling the initial game area with platforms
    while(m_highestGeneratedY > TopGenerationLimit)
        generateNextSafePlatform();
}

//updates all platforms by calling their update method with the delta time
void PlatformManager::update(float dt)
{
    for(auto& platform : m_platforms)
        platform->update(dt);
}

void PlatformManager::draw(sf::RenderWindow& window) const
{
    for(const auto& platform : m_platforms)
        platform->draw(window);
}

//camera movement
void PlatformManager::scroll(float dy)
{
    for(auto& platform : m_platforms)
        platform->move(dy);

    m_highestGeneratedY += dy;
}

void PlatformManager::removeOld(float windowHeight)
{
    m_platforms.erase(
        std::remove_if(
            m_platforms.begin(),
            m_platforms.end(),
            [windowHeight](const std::unique_ptr<Platform>& platform)
            {
                return platform->shouldRemove(windowHeight);
            }),
        m_platforms.end());
}

//making sure that there are always enough platforms generated above the player by generating new platforms until the highest generated Y is above the top generation limit
void PlatformManager::ensurePlatforms()
{
    while(m_highestGeneratedY > TopGenerationLimit)
        generateNextSafePlatform();
}

std::vector<std::unique_ptr<Platform>>& PlatformManager::platforms()
{
    return m_platforms;
}

const std::vector<std::unique_ptr<Platform>>& PlatformManager::platforms() const
{
    return m_platforms;
}


//generates a new safe platform above the last generated platform, ensuring that it is reachable from the last safe platform and does not overlap with existing platforms.
// It also has a chance to generate a breakable platform above the new safe platform.
void PlatformManager::generateNextSafePlatform()
{
    const float gap = randomFloat(95.f, 135.f);
    m_highestGeneratedY -= gap;

    const float minReachableX = std::max(MinX, m_lastSafeX - MaxHorizontalGap);
    const float maxReachableX = std::min(MaxX, m_lastSafeX + MaxHorizontalGap);
    m_lastSafeX = randomFloat(minReachableX, maxReachableX);

    std::unique_ptr<Platform> platform;
    if(randomInt(0, 99) < 70)
        platform = std::make_unique<NormalPlatform>(
            m_normalTexture,
            sf::Vector2f{m_lastSafeX, m_highestGeneratedY});
    else
        platform = std::make_unique<MovingPlatform>(
            m_movingTexture,
            sf::Vector2f{m_lastSafeX, m_highestGeneratedY});

    maybeAttachSpring(*platform);
    m_platforms.push_back(std::move(platform));

    if(randomInt(0, 99) < 35)
        maybeGenerateBreakable(m_highestGeneratedY + randomFloat(35.f, 75.f));
}

void PlatformManager::maybeGenerateBreakable(float nearY)
{
    for(int attempt = 0; attempt < 8; ++attempt)
    {
        const float x = randomFloat(MinX, MaxX);
        auto platform = std::make_unique<BreakablePlatform>(
            m_breakableTexture,
            sf::Vector2f{x, nearY});

        if(!overlapsExisting(platform->getBounds()))
        {
            m_platforms.push_back(std::move(platform));
            return;
        }
    }
}

void PlatformManager::maybeAttachSpring(Platform& platform)
{
    if(dynamic_cast<NormalPlatform*>(&platform) == nullptr)
        return;

    if(randomInt(0, 99) >= 25)
        return;

    const auto bounds = platform.getBounds();
    platform.attachSpring(std::make_unique<Spring>(
        m_springTexture,
        sf::Vector2f{bounds.position.x + 20.f, bounds.position.y - 36.f}));
}

bool PlatformManager::overlapsExisting(const sf::FloatRect& bounds) const
{
    for(const auto& platform : m_platforms)
    {
        const auto other = platform->getBounds();
        const sf::FloatRect padded{
            {other.position.x - 20.f, other.position.y - 35.f},
            {other.size.x + 40.f, other.size.y + 70.f}
        };

        if(bounds.findIntersection(padded))
            return true;
    }

    return false;
}

float PlatformManager::randomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_rng);
}

int PlatformManager::randomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_rng);
}
