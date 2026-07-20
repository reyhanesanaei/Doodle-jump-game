#include "States/SettingsState.hpp"

#include "Engine/Game.hpp"

#include <string>

namespace
{
    void fitToWindow(sf::Sprite& sprite)
    {
        const auto size = sprite.getTexture().getSize();
        if (size.x == 0 || size.y == 0)
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

SettingsState::SettingsState(Game& game)
    : m_game(game),
      m_background(game.textures().get("background")),
      m_backButton(game.textures().get("back_button")), //phase2
      m_titleText(game.fonts().get("main"), "SETTINGS", 52)
{
    fitToWindow(m_background);

    m_titleText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_titleText, 220.f);
    m_backButton.setCenteredPosition({300.f, 760.f}, {0.33f, 0.33f});
}

void SettingsState::handleEvent(const sf::Event& event)
{
    const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
    if (!mouse || mouse->button != sf::Mouse::Button::Left)
        return;

    if (m_backButton.contains(mouse->position))
        m_game.changeToMenu();
}

void SettingsState::update(float)
{
}

void SettingsState::render(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_titleText);
    m_backButton.draw(window);
}
