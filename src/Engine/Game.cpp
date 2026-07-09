#include "Engine/Game.hpp"

#include "States/GameOverState.hpp"
#include "States/GameplayState.hpp"
#include "States/MenuState.hpp"

#include <memory>

Game::Game()
    : m_window("Simple Doodle Jump", WindowWidth, WindowHeight),
      m_scores("highscore.txt")
{
    loadResources();
    changeToMenu();
    m_states.applyPendingState();
}

void Game::run()
{
    while(m_window.isOpen())
    {
        while(const auto event = m_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                m_window.close();
                continue;
            }

            m_states.handleEvent(*event);
        }

        const float dt = m_clock.restart().asSeconds();
        m_states.update(dt);

        m_window.clear(sf::Color::White);
        m_states.render(m_window.getRenderWindow());
        m_window.display();
    }
}

void Game::quit()
{
    m_window.close();
}

void Game::changeToMenu()
{
    m_states.changeState(std::make_unique<MenuState>(*this));
}

void Game::startGameplay()
{
    m_scores.resetCurrent();
    m_clock.restart();
    m_states.changeState(std::make_unique<GameplayState>(*this));
}

void Game::showGameOver()
{
    m_scores.finishRun();
    m_states.changeState(std::make_unique<GameOverState>(*this, m_scores.currentScore()));
}

Window& Game::window()
{
    return m_window;
}

ResourceManager<sf::Texture>& Game::textures()
{
    return m_textures;
}

ResourceManager<sf::Font>& Game::fonts()
{
    return m_fonts;
}

ScoreManager& Game::scores()
{
    return m_scores;
}

const ScoreManager& Game::scores() const
{
    return m_scores;
}

void Game::loadResources()
{
    m_textures.load("background", "assets/background.png");
    m_textures.load("player_left", "assets/left_doodle.png");
    m_textures.load("player_right", "assets/right_doodle.png");
    m_textures.load("platform_normal", "assets/normal_platform.png");
    m_textures.load("platform_moving", "assets/moving_platform.png");
    m_textures.load("platform_breakable", "assets/broken_platform.png");
    m_textures.load("spring", "assets/spring_sprite.png");
    m_textures.load("start_button", "assets/start_button.png");
    m_textures.load("restart_button", "assets/restart_button.png");
    m_textures.load("menu_button", "assets/menu_button.png");

    m_fonts.load("main", "fonts/ariblk.ttf");
}
