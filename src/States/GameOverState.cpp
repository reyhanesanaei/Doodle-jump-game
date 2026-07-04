#include "States/GameOverState.hpp"
#include "States/GameplayState.hpp"
#include "States/MenuState.hpp"
#include "Engine/Game.hpp"

namespace
{
    const std::string FONT_PATH = "fonts/ariblk.ttf";
}

GameOverState::GameOverState(Game& game)
    : State(game)
{
    sf::Font& font = m_game.getFontManager().get(FONT_PATH);

    const int score     = m_game.getScoreManager().getCurrentScore();
    const int highScore = m_game.getScoreManager().getHighScore();

    m_titleText.setFont(font);
    m_titleText.setString("YOU LOST");
    m_titleText.setCharacterSize(40);
    m_titleText.setFillColor(sf::Color(200, 30, 30));
    m_titleText.setPosition(60.f, 140.f);

    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(20);
    m_scoreText.setFillColor(sf::Color(60, 60, 60));
    m_scoreText.setString("SCORE: " + std::to_string(score));
    m_scoreText.setPosition(60.f, 210.f);

    m_highScoreText.setFont(font);
    m_highScoreText.setCharacterSize(20);
    m_highScoreText.setFillColor(sf::Color(60, 60, 60));
    m_highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
    m_highScoreText.setPosition(60.f, 240.f);

    m_restartButton = std::make_unique<Button>(
        font, "Restart", sf::Vector2f(160.f, 300.f), sf::Vector2f(160.f, 45.f));
    m_restartButton->setOnClick([this]() { restartGame(); });

    m_menuButton = std::make_unique<Button>(
        font, "Menu", sf::Vector2f(160.f, 355.f), sf::Vector2f(160.f, 45.f));
    m_menuButton->setOnClick([this]() { returnToMenu(); });
}

void GameOverState::handleEvent(const sf::Event& event)
{
    m_restartButton->handleEvent(event);
    m_menuButton->handleEvent(event);
}

void GameOverState::update(float /*deltaTime*/)
{
    // Gameplay updates are frozen on the Game Over screen by design (the
    // GameplayState that produced this screen has already been replaced).
}

void GameOverState::render(sf::RenderTarget& target)
{
    target.draw(m_titleText);
    target.draw(m_scoreText);
    target.draw(m_highScoreText);
    m_restartButton->draw(target);
    m_menuButton->draw(target);
}

void GameOverState::restartGame()
{
    // Restart goes straight into a fresh GameplayState, skipping the menu.
    m_game.getScoreManager().reset();
    m_game.getStateManager().changeState(std::make_unique<GameplayState>(m_game));
}

void GameOverState::returnToMenu()
{
    m_game.getStateManager().changeState(std::make_unique<MenuState>(m_game));
}