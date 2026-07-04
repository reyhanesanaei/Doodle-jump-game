#include "UI/Button.hpp"

Button::Button(sf::Font& font, const std::string& label,
               sf::Vector2f position, sf::Vector2f size)
    : m_idleColor(sf::Color(70, 130, 180))
    , m_hoverColor(sf::Color(100, 160, 210))
    , m_isHovered(false)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(m_idleColor);

    m_text.setFont(font);
    m_text.setString(label);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
    centerText();
}

void Button::setOnClick(std::function<void()> callback)
{
    m_onClick = std::move(callback);
}

void Button::setColors(const sf::Color& idle, const sf::Color& hover)
{
    m_idleColor = idle;
    m_hoverColor = hover;
    m_shape.setFillColor(m_isHovered ? m_hoverColor : m_idleColor);
}

bool Button::contains(sf::Vector2f point) const
{
    return m_shape.getGlobalBounds().contains(point);
}

void Button::centerText()
{
    const sf::FloatRect textBounds = m_text.getLocalBounds();
    const sf::FloatRect shapeBounds = m_shape.getGlobalBounds();

    m_text.setOrigin(textBounds.left + textBounds.width / 2.f,
                      textBounds.top + textBounds.height / 2.f);
    m_text.setPosition(shapeBounds.left + shapeBounds.width / 2.f,
                        shapeBounds.top + shapeBounds.height / 2.f);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x),
                                     static_cast<float>(event.mouseMove.y));
        m_isHovered = contains(mousePos);
        m_shape.setFillColor(m_isHovered ? m_hoverColor : m_idleColor);
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                     static_cast<float>(event.mouseButton.y));
        if (contains(mousePos) && m_onClick)
            m_onClick();
    }
}

void Button::draw(sf::RenderTarget& target) const
{
    target.draw(m_shape);
    target.draw(m_text);
}