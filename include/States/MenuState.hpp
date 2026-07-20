#pragma once

#include "Engine/StateManager.hpp"
#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>

class Game;

class MenuState : public IState
{
public:
    explicit MenuState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void refreshText();

    Game& m_game;
    sf::Sprite m_background;
    Button m_startButton;
    sf::Text m_titleText;
    sf::Text m_highScoreText;
    sf::Text m_hintText;

    Button m_settingsButton;    //phase2
};
