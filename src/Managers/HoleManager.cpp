#include "Managers/HoleManager.hpp"

#include <algorithm>

void HoleManager::update(float dt)
{
    for(auto& hole : m_holes)
        hole.update(dt);

    m_holes.erase(
        std::remove_if(
            m_holes.begin(),
            m_holes.end(),
            [](const Hole& hole)
            {
                return hole.shouldRemove();
            }),
        m_holes.end());
}

void HoleManager::draw(sf::RenderWindow& window) const
{
    for(const auto& hole : m_holes)
        hole.draw(window);
}

void HoleManager::move(float dy)
{
    for(auto& hole : m_holes)
        hole.move(dy);
}

void HoleManager::addHole(const sf::Texture& texture,
                          sf::Vector2f position,
                          HoleType type)
{
    m_holes.emplace_back(texture, position, type);
}

std::vector<Hole>& HoleManager::holes()
{
    return m_holes;
}

const std::vector<Hole>& HoleManager::holes() const
{
    return m_holes;
}