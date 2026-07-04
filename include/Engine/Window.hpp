#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// Thin wrapper around sf::RenderWindow. Keeping it as its own class (rather
// than letting Game hold an sf::RenderWindow directly) means the rest of the
// codebase depends on a small, app-specific interface instead of the full
// SFML window API, and the fixed-size / non-resizable rule lives in exactly
// one place.
class Window
{
public:
    Window(const std::string& title, unsigned int width, unsigned int height);

    bool isOpen() const;
    bool pollEvent(sf::Event& event);

    void clear(const sf::Color& color = sf::Color::White);
    void display();
    void close();

    sf::RenderWindow& getRenderWindow();
    sf::Vector2u getSize() const;

private:
    sf::RenderWindow m_window;
};