#include "States/GameplayState.hpp"

#include "Engine/Game.hpp"

namespace
{
    void fitToWindow(sf::Sprite& sprite)
    {
        const auto size = sprite.getTexture().getSize();
        if(size.x == 0 || size.y == 0)
            return;

        sprite.setScale({
            static_cast<float>(Game::WindowWidth) / static_cast<float>(size.x),
            static_cast<float>(Game::WindowHeight) / static_cast<float>(size.y)
        });
    }
}

GameplayState::GameplayState(Game& game)
    : m_game(game),
      m_background(game.textures().get("background")),
      m_player(
          game.textures().get("player_left"),
          game.textures().get("player_right")),
      m_platforms(
          game.textures().get("platform_normal"),
          game.textures().get("platform_moving"),
          game.textures().get("platform_breakable"),
          game.textures().get("spring")),
      m_hud(game.fonts().get("main"))
{
    fitToWindow(m_background);
    m_hud.update(m_game.scores().currentScore(), m_game.scores().highScore());
}

void GameplayState::handleEvent(const sf::Event&)
{
}

void GameplayState::update(float dt)
{
    m_player.update(dt);
    m_platforms.update(dt);

    if(Spring* spring = m_collisions.findLandedSpring(m_player, m_platforms))
    {
        m_player.springJump();
        spring->deactivate();
    }
    else if(Platform* platform = m_collisions.findLandedPlatform(m_player, m_platforms))
    {
        platform->onPlayerLanded(m_player);
    }

    constexpr float CameraLockY = 360.f;
    if(m_player.getY() < CameraLockY)
    {
        const float offset = CameraLockY - m_player.getY();
        m_player.move(offset);
        m_platforms.scroll(offset);
        m_game.scores().addHeight(offset);
    }

    m_platforms.removeOld(static_cast<float>(Game::WindowHeight));
    m_platforms.ensurePlatforms();
    m_hud.update(m_game.scores().currentScore(), m_game.scores().highScore());

    if(m_player.getY() > static_cast<float>(Game::WindowHeight) + 80.f)
        m_game.showGameOver();
}

void GameplayState::render(sf::RenderWindow& window)
{
    window.draw(m_background);
    m_platforms.draw(window);
    m_player.draw(window);
    m_hud.draw(window);
}
