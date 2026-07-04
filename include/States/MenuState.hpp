#pragma once

#include "States/State.hpp"
#include "UI/Button.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Main menu: title, all-time high score, and a "Start" button that begins
// a new gameplay session.
class MenuState : public State
{
public:
    explicit MenuState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;

private:
    void startGame();

    sf::Text m_titleText;
    sf::Text m_highScoreText;
    std::unique_ptr<Button> m_startButton;
};