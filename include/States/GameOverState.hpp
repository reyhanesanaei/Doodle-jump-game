#pragma once

#include "States/State.hpp"
#include "UI/Button.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// "YOU LOST" screen: shows the final score and the all-time high score,
// with Restart (-> straight back into a new GameplayState) and Main Menu
// buttons.
class GameOverState : public State
{
public:
    explicit GameOverState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;

private:
    void restartGame();
    void returnToMenu();

    sf::Text m_titleText;
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
    std::unique_ptr<Button> m_restartButton;
    std::unique_ptr<Button> m_menuButton;
};