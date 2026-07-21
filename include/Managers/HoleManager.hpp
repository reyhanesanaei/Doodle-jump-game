#pragma once

#include "Entities/Hole.hpp"

#include <vector>

class HoleManager
{
public:
    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    void move(float dy);

    void addHole(const sf::Texture& texture,
                 sf::Vector2f position,
                 HoleType type);

    std::vector<Hole>& holes();
    const std::vector<Hole>& holes() const;

private:
    std::vector<Hole> m_holes;
};