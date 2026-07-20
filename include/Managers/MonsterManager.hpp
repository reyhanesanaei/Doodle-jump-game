#pragma once

#include "Entities/Monster.hpp"
#include "Managers/PlatformManager.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>

class MonsterManager
{
public:
    MonsterManager() = default;

    void addMonster(const sf::Texture& texture,
                    sf::Vector2f position,
                    MonsterType type);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    void move(float dy);

    std::vector<Monster>& monsters();
    const std::vector<Monster>& monsters() const;

    void spawnOnPlatforms(
    PlatformManager& platformManager,
    const sf::Texture& monster1Texture,
    const sf::Texture& monster2Texture);

    void updateSpawns(
    PlatformManager& platformManager,
    const sf::Texture& monster1Texture,
    const sf::Texture& monster2Texture);

private:
    std::vector<Monster> m_monsters;
    std::unordered_set<const Platform*> m_usedPlatforms;
};