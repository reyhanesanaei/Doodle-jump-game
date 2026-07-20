#include "Engine/Window.hpp"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : m_window(
          sf::VideoMode(sf::Vector2u{width, height}),
          title,
          sf::Style::Titlebar | sf::Style::Close)
{
    m_window.setFramerateLimit(60);
}

bool Window::isOpen() const
{
    return m_window.isOpen();
}

void Window::close()
{
    m_window.close();
}

std::optional<sf::Event> Window::pollEvent()
{
    return m_window.pollEvent();
}

void Window::clear(const sf::Color& color)
{
    m_window.clear(color);
}

void Window::display()
{
    m_window.display();
}

sf::RenderWindow& Window::getRenderWindow()
{
    return m_window;
}

const sf::RenderWindow& Window::getRenderWindow() const
{
    return m_window;
}
