#include "UI/HUD.hpp"

#include <string>

HUD::HUD(const sf::Font& font)
    : m_scoreText(font, "Score: 0", 28),
      m_highScoreText(font, "High: 0", 20)
{
    m_scoreText.setFillColor(sf::Color::Red);
    m_scoreText.setOutlineColor(sf::Color::White);
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition({16.f, 14.f});

    m_highScoreText.setFillColor(sf::Color(35, 45, 55));
    m_highScoreText.setOutlineColor(sf::Color::White);
    m_highScoreText.setOutlineThickness(2.f);
    m_highScoreText.setPosition({16.f, 52.f});
}

void HUD::update(int score, int highScore)
{
    m_scoreText.setString("Score: " + std::to_string(score));
    m_highScoreText.setString("High: " + std::to_string(highScore));
}

void HUD::draw(sf::RenderWindow& window) const
{
    window.draw(m_scoreText);
    window.draw(m_highScoreText);
}
