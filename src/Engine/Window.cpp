#include "Engine/Window.hpp"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : m_window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close)
{
    // No sf::Style::Resize -> the window cannot be resized by the user,
    // satisfying the "fixed size" requirement.
    m_window.setFramerateLimit(60);
}

bool Window::isOpen() const
{
    return m_window.isOpen();
}

bool Window::pollEvent(sf::Event& event)
{
    return m_window.pollEvent(event);
}

void Window::clear(const sf::Color& color)
{
    m_window.clear(color);
}

void Window::display()
{
    m_window.display();
}

void Window::close()
{
    m_window.close();
}

sf::RenderWindow& Window::getRenderWindow()
{
    return m_window;
}

sf::Vector2u Window::getSize() const
{
    return m_window.getSize();
}