#include "UI/HUD.hpp"
#include <string>

HUD::HUD(sf::Font& font)
{
    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(28);
    m_scoreText.setFillColor(sf::Color::Black);
    m_scoreText.setPosition(15.f, 10.f);
    setScore(0);
}

void HUD::setScore(int score)
{
    m_scoreText.setString(std::to_string(score));
}

void HUD::draw(sf::RenderTarget& target) const
{
    target.draw(m_scoreText);
}