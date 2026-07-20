#pragma once

#include "Engine/ResourceManager.hpp"
#include "Engine/StateManager.hpp"
#include "Engine/Window.hpp"
#include "Managers/ScoreManager.hpp"

#include <SFML/Audio.hpp>
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
    void changeToSettings();

    void playMenuMusic();
    void stopMenuMusic();
    void playLoseSound();

    Window& window();
    ResourceManager<sf::Texture>& textures();
    ResourceManager<sf::Font>& fonts();
    ScoreManager& scores();
    const ScoreManager& scores() const;

    //phase2
    
    //

private:

    void loadResources();

    Window m_window;
    ResourceManager<sf::Texture> m_textures;
    ResourceManager<sf::Font> m_fonts;
    StateManager m_states;
    ScoreManager m_scores;
    sf::Clock m_clock;

    sf::Music m_menuMusic;
    sf::SoundBuffer m_looseBuffer;
    sf::Sound m_looseSound;
};
