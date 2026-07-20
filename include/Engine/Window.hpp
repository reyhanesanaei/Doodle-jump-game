#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

class Window
{
public:
    Window(const std::string& title, unsigned int width, unsigned int height);

    bool isOpen() const;
    void close();
    std::optional<sf::Event> pollEvent();

    void clear(const sf::Color& color = sf::Color::Black);
    void display();

    sf::RenderWindow& getRenderWindow();
    const sf::RenderWindow& getRenderWindow() const;

private:
    sf::RenderWindow m_window;
};
