#pragma once

#include "Engine/StateManager.hpp"
#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>

class Game;

class SettingsState : public IState
{
public:
    explicit SettingsState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    Game& m_game;
    sf::Sprite m_background;
    Button m_backButton;
    sf::Text m_titleText;
};
