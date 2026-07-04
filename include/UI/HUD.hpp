#pragma once

#include <SFML/Graphics.hpp>

// Heads-up display shown during gameplay: just the live score, top-left,
// per the project's requirement that score be visible "in real time".
// Kept separate from GameplayState so the visual layout of the HUD can be
// redesigned later without touching gameplay logic.
class HUD
{
public:
    explicit HUD(sf::Font& font);

    void setScore(int score);
    void draw(sf::RenderTarget& target) const;

private:
    sf::Text m_scoreText;
};