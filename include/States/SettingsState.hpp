#pragma once

#include "Engine/StateManager.hpp"
#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>
//for slider of volume
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
//

class Game;

class SettingsState : public IState
{
public:
    explicit SettingsState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

    bool m_draggingSlider = false;  //for mouse dragging of slider knob

private:
    Game& m_game;
    sf::Sprite m_background;
    Button m_backButton;
    sf::Text m_titleText;

    sf::Text m_volumeText;  
    //for slider of volume
    sf::RectangleShape m_sliderBar;
    sf::CircleShape m_sliderKnob;

    float m_volume = 60.f;

    //game mode: easy, medium, hard
    sf::Text m_gameModeText;

    sf::Text m_easyText;
    sf::Text m_normalText;
    sf::Text m_hardText;

    int m_selectedMode = 1; // 0 = Easy, 1 = Normal, 2 = Hard
};
