#pragma once

#include <SFML/Graphics.hpp>

class HUD
{
public:
    explicit HUD(const sf::Font& font);

    void update(int score, int highScore);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
};
