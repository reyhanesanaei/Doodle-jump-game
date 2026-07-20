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
      m_backButton(game.textures().get("back_button")),
      m_titleText(game.fonts().get("main"), "SETTINGS", 52),
      m_volumeText(game.fonts().get("main"), "Volume", 32),  //volume text
      m_gameModeText(game.fonts().get("main"), "Game Mode", 32),
      //game mode: easy, medium, hard
      m_easyText(game.fonts().get("main"), "Easy", 28),
      m_normalText(game.fonts().get("main"), "Normal", 28),
      m_hardText(game.fonts().get("main"), "Hard", 28)
{
    fitToWindow(m_background);

    m_titleText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_titleText, 220.f);
    m_backButton.setCenteredPosition({300.f, 760.f}, {0.33f, 0.33f});   //phase2. back button
//phase2. volume text
    centerText(m_volumeText, 400.f);    
    m_volumeText.setFillColor(sf::Color(35, 45, 55));
    m_volumeText.setPosition({300.f, 320.f});
//slider of volume
    m_sliderBar.setSize({220.f, 6.f});
    m_sliderBar.setFillColor(sf::Color(170, 170, 170));
    m_sliderBar.setPosition({200.f, 420.f});

    m_sliderKnob.setRadius(10.f);
    m_sliderKnob.setOrigin({10.f, 10.f});
    m_sliderKnob.setFillColor(sf::Color(40, 170, 255));

    float knobX = 200.f + (220.f * (m_volume / 100.f));
    // align knob vertically to the center of the slider bar
    float knobY = m_sliderBar.getPosition().y + m_sliderBar.getSize().y / 2.f;
    m_sliderKnob.setPosition({knobX, knobY});

//game mode: easy, medium, hard
    m_gameModeText.setFont(game.fonts().get("main"));
    m_gameModeText.setString("Game Mode");
    m_gameModeText.setCharacterSize(32);
    m_gameModeText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_gameModeText, 500.f);

    m_easyText.setFont(game.fonts().get("main"));
    m_easyText.setString("Easy");
    m_easyText.setCharacterSize(24);
    m_easyText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_easyText, 550.f);

    m_normalText.setFont(game.fonts().get("main"));
    m_normalText.setString("Normal");
    m_normalText.setCharacterSize(24);
    m_normalText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_normalText, 600.f);

    m_hardText.setFont(game.fonts().get("main"));
    m_hardText.setString("Hard");
    m_hardText.setCharacterSize(24);
    m_hardText.setFillColor(sf::Color(35, 45, 55));
    centerText(m_hardText, 650.f);
//
}

void SettingsState::handleEvent(const sf::Event& event)
{
    // Handle mouse button press
    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouse->button == sf::Mouse::Button::Left)
        {
            // Check if Back button was clicked
            if (m_backButton.contains(mouse->position))
            {
                m_game.changeToMenu();
            }

            // Check if slider knob was clicked
            if (m_sliderKnob.getGlobalBounds().contains(
                sf::Vector2f(mouse->position)))
            {
                m_draggingSlider = true;
            }

            // Check if Easy mode was clicked
            if (m_easyText.getGlobalBounds().contains(sf::Vector2f(mouse->position)))
            {
                m_selectedMode = 0;
            }

            // Check if Normal mode was clicked
            if (m_normalText.getGlobalBounds().contains(sf::Vector2f(mouse->position)))
            {
                m_selectedMode = 1;
            }

            // Check if Hard mode was clicked
            if (m_hardText.getGlobalBounds().contains(sf::Vector2f(mouse->position)))
            {
                m_selectedMode = 2;
            }
        }

        m_easyText.setFillColor(
            m_selectedMode == 0 ? sf::Color::Blue : sf::Color::Black);

        m_normalText.setFillColor(
            m_selectedMode == 1 ? sf::Color::Blue : sf::Color::Black);

        m_hardText.setFillColor(
            m_selectedMode == 2 ? sf::Color::Blue : sf::Color::Black);
    }

    // Handle mouse button release - stop dragging
    if (event.is<sf::Event::MouseButtonReleased>())
    {
        m_draggingSlider = false;
    }

    // Handle mouse movement - update slider knob position and volume
    if (const auto* mouse = event.getIf<sf::Event::MouseMoved>())
    {
        if (m_draggingSlider)
        {
            float x = static_cast<float>(mouse->position.x);

            // Clamp x position to slider bar bounds
            const float left = m_sliderBar.getPosition().x;
            const float right = left + m_sliderBar.getSize().x;

            if (x < left)
                x = left;
            if (x > right)
                x = right;

            // Update knob position, maintaining its vertical alignment
            m_sliderKnob.setPosition({x, m_sliderKnob.getPosition().y});

            // Convert knob position to volume percentage (0-100)
            m_volume = ((x - left) / m_sliderBar.getSize().x) * 100.f;
        }
    }
}

void SettingsState::update(float)
{
}

void SettingsState::render(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_titleText);
    window.draw(m_volumeText);  
//phase2.
    m_backButton.draw(window);   //back button
    window.draw(m_volumeText);  //volume text
    //slider of volume
    window.draw(m_sliderBar);
    window.draw(m_sliderKnob);

//game mode: easy, medium, hard
    window.draw(m_gameModeText);
    window.draw(m_easyText);
    window.draw(m_normalText);
    window.draw(m_hardText);
}
