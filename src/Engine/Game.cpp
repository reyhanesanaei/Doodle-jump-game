#include "Engine/Game.hpp"

#include "States/GameOverState.hpp"
#include "States/GameplayState.hpp"
#include "States/MenuState.hpp"
#include "States/SettingsState.hpp"

#include <memory>
#include <stdexcept>

Game::Game()
    : m_window("Simple Doodle Jump", WindowWidth, WindowHeight),
      m_scores("highscore.txt"),
      m_looseSound(m_looseBuffer)
{
    loadResources();

    if (!m_looseBuffer.loadFromFile("sounds/Loosing_Sound.wav"))
    {
        throw std::runtime_error("Couldn't load loose sound.");
    }

    m_looseSound.setBuffer(m_looseBuffer);
    m_looseSound.setVolume(80.f);

    if (!m_menuMusic.openFromFile("sounds/MainMenu_Song.flac"))
    {
        throw std::runtime_error("Couldn't load menu sound.");
    }

    m_menuMusic.setLooping(true);
    m_menuMusic.setVolume(60.f);

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
    playMenuMusic();
    m_states.changeState(std::make_unique<MenuState>(*this));
}

//phase2
/*void Game::changeToSettings()
{
    m_states.changeState(std::make_unique<SettingsState>(*this));
}
*/
//

void Game::startGameplay()
{
    m_scores.resetCurrent();
    m_clock.restart();
    stopMenuMusic();
    m_states.changeState(std::make_unique<GameplayState>(*this));
}

void Game::showGameOver()
{
    m_scores.finishRun();
    playLoseSound();
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

void Game::playMenuMusic()
{
    if (m_menuMusic.getStatus() != sf::SoundSource::Status::Playing)
    {
        m_menuMusic.play();
    }
}

void Game::stopMenuMusic()
{
    m_menuMusic.stop();
}

void Game::playLoseSound()
{
    m_looseSound.play();
}

void Game::loadResources()
{
    m_textures.load("background", "assets/background.png");
    m_textures.load("player_left", "assets/player/left_doodle.png");
    m_textures.load("player_right", "assets/player/right_doodle.png");
    m_textures.load("platform_normal", "assets/normal_platform.png");
    m_textures.load("platform_moving", "assets/moving_platform.png");
    m_textures.load("platform_breakable", "assets/broken_platform.png");
    m_textures.load("spring", "assets/spring_sprite.png");
    m_textures.load("start_button", "assets/ui/start_button.png");
    m_textures.load("restart_button", "assets/ui/restart_button.png");
    m_textures.load("menu_button", "assets/ui/menu_button.png");

    m_fonts.load("main", "fonts/ariblk.ttf");

    //phase 2
    m_textures.load("blueMonster", "assets/monsters/BlueMonster.png");
    m_textures.load("greenMonster","assets/monsters/green_monster.png");

    m_textures.load("hole_small","assets/holes/hole.png");
    m_textures.load("hole_large" , "assets/holes/hole@2x.png");

    m_textures.load("Nose" , "assets/player/Nose.png");
    m_textures.load("shooting_doodle" , "assets/player/Shooting@Pose.png");

    m_textures.load("back_button" , "assets/ui/back_button.png");
    m_textures.load("settings_button" , "assets/ui/Settings_button.png");

}
