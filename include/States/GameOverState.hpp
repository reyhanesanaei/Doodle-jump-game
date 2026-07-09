#pragma once

#include "Engine/StateManager.hpp"
#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>

class Game;

class GameOverState : public IState
{
public:
    GameOverState(Game& game, int finalScore);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void refreshText();

    Game& m_game;
    int m_finalScore;
    sf::Sprite m_background;
    Button m_restartButton;
    Button m_menuButton;
    sf::Text m_lostText;
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
};
