#include "Managers/MonsterManager.hpp"
#include <algorithm>

void MonsterManager::addMonster(const sf::Texture& texture,
                                sf::Vector2f position,
                                MonsterType type)
{
    m_monsters.emplace_back(texture, position, type);
}

void MonsterManager::update(float dt)
{
    for (auto& monster : m_monsters)
    {
        monster.update(dt);
    }

    m_monsters.erase(
    std::remove_if(
            m_monsters.begin(),
            m_monsters.end(),
            [](const Monster& monster)
            {
                return monster.getBounds().position.y > 1100.f || monster.isDead();
            }),
        m_monsters.end());
}

void MonsterManager::draw(sf::RenderWindow& window) const
{
    for (const auto& monster : m_monsters)
    {
        monster.draw(window);
    }
}

void MonsterManager::move(float dy)
{
    for (auto& monster : m_monsters)
    {
        monster.move(dy);
    }
}

std::vector<Monster>& MonsterManager::monsters()
{
    return m_monsters;
}

const std::vector<Monster>& MonsterManager::monsters() const
{
    return m_monsters;
}

void MonsterManager::spawnOnPlatforms(
    PlatformManager& platformManager,
    const sf::Texture& monster1Texture,
    const sf::Texture& monster2Texture)
{
    m_monsters.clear();

    auto& platforms = platformManager.platforms();

    for (size_t i = 0; i < platforms.size(); i++)
    {
        // 20% chance
        if (std::rand() % 5 != 0)
            continue;

        auto bounds = platforms[i]->getBounds();

        sf::Vector2f pos(
            bounds.position.x,
            bounds.position.y - 60.f
        );

        if (std::rand() % 2 == 0)
        {
            addMonster(
                monster1Texture,
                pos,
                MonsterType::Blue
            );
        }
        else
        {
            addMonster(
                monster2Texture,
                pos,
                MonsterType::Green
            );
        }
    }
}