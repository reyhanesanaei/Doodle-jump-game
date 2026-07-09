#include "States/GameOverState.hpp"

#include "Engine/Game.hpp"

#include <string>

namespace
{
    void fitToWindow(sf::Sprite& sprite)
    {
        const auto size = sprite.getTexture().getSize();
        if(size.x == 0 || size.y == 0)
            return;

        sprite.setScale({
            static_cast<float>(Game::WindowWidth) / static_cast<float>(size.x),
            static_cast<float>(Game::WindowHeight) / static_cast<float>(size.y)
        });
    }

    void centerText(sf::Text& text, float y)
    {
        const auto bounds = text.getLocalBounds();
        text.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });
        text.setPosition({Game::WindowWidth / 2.f, y});
    }
}

GameOverState::GameOverState(Game& game, int finalScore)
    : m_game(game),
      m_finalScore(finalScore),
      m_background(game.textures().get("background")),
      m_restartButton(game.textures().get("restart_button")),
      m_menuButton(game.textures().get("menu_button")),
      m_lostText(game.fonts().get("main"), "YOU LOST", 62),
      m_scoreText(game.fonts().get("main"), "", 28),
      m_highScoreText(game.fonts().get("main"), "", 24)
{
    fitToWindow(m_background);

    m_lostText.setFillColor(sf::Color::Red);
    m_scoreText.setFillColor(sf::Color(35, 45, 55));
    m_highScoreText.setFillColor(sf::Color(35, 45, 55));

    m_restartButton.setCenteredPosition({300.f, 590.f}, {0.65f, 0.65f});
    m_menuButton.setCenteredPosition({300.f, 700.f}, {0.65f, 0.65f});

    centerText(m_lostText, 370.f);
    refreshText();
}

void GameOverState::handleEvent(const sf::Event& event)
{
    const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
    if(!mouse || mouse->button != sf::Mouse::Button::Left)
        return;

    if(m_restartButton.contains(mouse->position))
        m_game.startGameplay();
    else if(m_menuButton.contains(mouse->position))
        m_game.changeToMenu();
}

void GameOverState::update(float)
{
}

void GameOverState::render(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_lostText);
    window.draw(m_scoreText);
    window.draw(m_highScoreText);
    m_restartButton.draw(window);
    m_menuButton.draw(window);
}

void GameOverState::refreshText()
{
    m_scoreText.setString("SCORE: " + std::to_string(m_finalScore));
    m_highScoreText.setString("HIGH SCORE: " + std::to_string(m_game.scores().highScore()));

    centerText(m_scoreText, 455.f);
    centerText(m_highScoreText, 505.f);
}
