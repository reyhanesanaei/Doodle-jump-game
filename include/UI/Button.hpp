#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

// Reusable clickable button: a rectangle + centered label + hover highlight
// + click callback. Used by every menu (Main Menu's "Start", Game Over's
// "Restart" / "Menu") so click-handling logic is written exactly once.
class Button
{
public:
    Button(sf::Font& font, const std::string& label,
           sf::Vector2f position, sf::Vector2f size);

    void setOnClick(std::function<void()> callback);
    void setColors(const sf::Color& idle, const sf::Color& hover);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

private:
    bool contains(sf::Vector2f point) const;
    void centerText();

    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::function<void()> m_onClick;

    sf::Color m_idleColor;
    sf::Color m_hoverColor;
    bool m_isHovered;
};