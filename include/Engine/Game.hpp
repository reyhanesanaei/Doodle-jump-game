#pragma once

#include "Engine/ResourceManager.hpp"
#include "Engine/StateManager.hpp"
#include "Engine/Window.hpp"
#include "Managers/ScoreManager.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    static constexpr unsigned int WindowWidth = 600;
    static constexpr unsigned int WindowHeight = 1000;

    Game();

    void run();
    void quit();

    void changeToMenu();
    void startGameplay();
    void showGameOver();

    Window& window();
    ResourceManager<sf::Texture>& textures();
    ResourceManager<sf::Font>& fonts();
    ScoreManager& scores();
    const ScoreManager& scores() const;

private:
    void loadResources();

    Window m_window;
    ResourceManager<sf::Texture> m_textures;
    ResourceManager<sf::Font> m_fonts;
    StateManager m_states;
    ScoreManager m_scores;
    sf::Clock m_clock;
};
