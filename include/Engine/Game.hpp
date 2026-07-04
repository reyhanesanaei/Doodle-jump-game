#pragma once

#include "Engine/Window.hpp"
#include "Engine/StateManager.hpp"
#include "Engine/ResourceManager.hpp"
#include "Managers/ScoreManager.hpp"
#include <SFML/Graphics.hpp>

// Top-level owner of every long-lived system: the Window, the StateManager
// (which holds whichever of Menu/Gameplay/GameOver is active), the shared
// resource caches, and the ScoreManager. States receive a Game& reference
// and reach all of these through Game's accessors, so no system has to be
// passed around individually.
class Game
{
public:
    Game();

    void run();

    Window& getWindow();
    StateManager& getStateManager();
    TextureManager& getTextureManager();
    FontManager& getFontManager();
    ScoreManager& getScoreManager();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    static constexpr unsigned int WINDOW_WIDTH = 480;
    static constexpr unsigned int WINDOW_HEIGHT = 800;

    Window m_window;
    StateManager m_stateManager;
    TextureManager m_textureManager;
    FontManager m_fontManager;
    ScoreManager m_scoreManager;

    sf::Clock m_clock;
};