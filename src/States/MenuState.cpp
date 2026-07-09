#include "States/MenuState.hpp"

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

MenuState::MenuState(Game& game)
    : m_game(game),
      m_background(game.textures().get("background")),
      m_startButton(game.textures().get("start_button")),
      m_titleText(game.fonts().get("main"), "DOODLE JUMP", 56),
      m_highScoreText(game.fonts().get("main"), "", 26),
      m_hintText(game.fonts().get("main"), "Use Left / Right arrows to move", 16)
{
    fitToWindow(m_background);

    m_titleText.setFillColor(sf::Color(35, 45, 55));
    m_highScoreText.setFillColor(sf::Color(35, 45, 55));
    m_hintText.setFillColor(sf::Color(35, 45, 55));

    m_startButton.setCenteredPosition({300.f, 560.f}, {0.65f, 0.65f});

    centerText(m_titleText, 245.f);
    centerText(m_hintText, 715.f);
    refreshText();
}

void MenuState::handleEvent(const sf::Event& event)
{
    const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
    if(!mouse || mouse->button != sf::Mouse::Button::Left)
        return;

    if(m_startButton.contains(mouse->position))
        m_game.startGameplay();
}

void MenuState::update(float)
{
}

void MenuState::render(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_titleText);
    window.draw(m_highScoreText);
    m_startButton.draw(window);
    window.draw(m_hintText);
}

void MenuState::refreshText()
{
    m_highScoreText.setString("HIGH SCORE: " + std::to_string(m_game.scores().highScore()));
    centerText(m_highScoreText, 345.f);
}
