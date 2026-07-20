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
      m_titleText(game.fonts().get("main"), "SETTINGS", 52),
      m_volumeText(game.fonts().get("main"), "Volume", 32)  //phase2. volume text
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
        }
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
}
