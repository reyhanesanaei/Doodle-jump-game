#include "States/MenuState.hpp"
#include "States/GameplayState.hpp"
#include "Engine/Game.hpp"

namespace
{
    const std::string FONT_PATH = "fonts/ariblk.ttf";
}

MenuState::MenuState(Game& game)
    : State(game)
{
    sf::Font& font = m_game.getFontManager().get(FONT_PATH);

    m_titleText.setFont(font);
    m_titleText.setString("DOODLE JUMP");
    m_titleText.setCharacterSize(40);
    m_titleText.setFillColor(sf::Color(60, 60, 60));
    m_titleText.setPosition(50.f, 120.f);

    m_highScoreText.setFont(font);
    m_highScoreText.setCharacterSize(20);
    m_highScoreText.setFillColor(sf::Color(60, 60, 60));
    m_highScoreText.setString("HIGH SCORE: " +
                               std::to_string(m_game.getScoreManager().getHighScore()));
    m_highScoreText.setPosition(50.f, 190.f);

    m_startButton = std::make_unique<Button>(
        font, "Start", sf::Vector2f(160.f, 260.f), sf::Vector2f(160.f, 50.f));
    m_startButton->setOnClick([this]() { startGame(); });
}

void MenuState::handleEvent(const sf::Event& event)
{
    m_startButton->handleEvent(event);
}

void MenuState::update(float /*deltaTime*/)
{
    // Nothing animates on the menu itself; present for interface symmetry
    // and to leave room for future polish (e.g. an idle animation).
}

void MenuState::render(sf::RenderTarget& target)
{
    target.draw(m_titleText);
    target.draw(m_highScoreText);
    m_startButton->draw(target);
}

void MenuState::startGame()
{
    m_game.getScoreManager().reset();
    m_game.getStateManager().changeState(std::make_unique<GameplayState>(m_game));
}