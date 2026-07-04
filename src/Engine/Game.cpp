#include "Engine/Game.hpp"
#include "States/MenuState.hpp"

Game::Game()
    : m_window("Doodle Jump", WINDOW_WIDTH, WINDOW_HEIGHT)
{
    // The game always boots into the main menu. The actual switch-over
    // happens inside the first StateManager::update() call in run(), via
    // the deferred "pending state" mechanism.
    m_stateManager.changeState(std::make_unique<MenuState>(*this));
}

void Game::run()
{
    while (m_window.isOpen())
    {
        const float deltaTime = m_clock.restart().asSeconds();

        processEvents();   // 1. process events
        update(deltaTime);  // 2. update game objects
        render();            // 3. render / draw
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            continue;
        }
        m_stateManager.handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    m_stateManager.update(deltaTime);
}

void Game::render()
{
    m_window.clear(sf::Color(245, 245, 220));
    m_stateManager.render(m_window.getRenderWindow());
    m_window.display();
}

Window& Game::getWindow() { return m_window; }
StateManager& Game::getStateManager() { return m_stateManager; }
TextureManager& Game::getTextureManager() { return m_textureManager; }
FontManager& Game::getFontManager() { return m_fontManager; }
ScoreManager& Game::getScoreManager() { return m_scoreManager; }