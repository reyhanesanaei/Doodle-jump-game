#pragma once

// GameplayState wires together the Player and the platform world. It
// assumes the following public interface from classes that live in other
// sections of this project (Entities/Player.hpp, Managers/PlatformManager.hpp
// — not included in this batch):
//
//   class Player {
//   public:
//       explicit Player(TextureManager& textures);
//       void update(float deltaTime);          // input, gravity, jump, wrap
//       float consumeScrollOffset();            // upward progress this frame, then resets to 0
//       sf::Vector2f getPosition() const;
//       void draw(sf::RenderTarget& target) const;
//   };
//
//   class PlatformManager {
//   public:
//       explicit PlatformManager(TextureManager& textures);
//       void update(float deltaTime, float scrollOffset); // scroll + spawn + despawn
//       void resolveCollisions(Player& player);            // landing / breaking / springs
//       void draw(sf::RenderTarget& target) const;
//   };
//
// Once those two headers exist with this interface, GameplayState compiles
// and runs as-is.

#include "States/GameplayState.hpp"
#include "States/GameOverState.hpp"
#include "Engine/Game.hpp"
#include "Entities/Player.hpp"
#include "Managers/PlatformManager.hpp"

namespace
{
    const std::string FONT_PATH = "fonts/ariblk.ttf";
}

GameplayState::GameplayState(Game& game)
    : State(game)
    , m_player(std::make_unique<Player>(game.getTextureManager()))
    , m_platformManager(std::make_unique<PlatformManager>(game.getTextureManager()))
    , m_hud(game.getFontManager().get(FONT_PATH))
{
}

// Defined here (not = default in the header) because Player and
// PlatformManager are only complete types in this translation unit; the
// unique_ptr destructors need that completeness.
GameplayState::~GameplayState() = default;

void GameplayState::handleEvent(const sf::Event& /*event*/)
{
    // Left/Right movement is read directly from live keyboard state every
    // frame inside Player::update() rather than from key-pressed events,
    // since continuous, delta-time-based movement needs to know whether a
    // key is *currently held*, not just when it was pressed.
}

void GameplayState::update(float deltaTime)
{
    m_player->update(deltaTime);

    const float scrollOffset = m_player->consumeScrollOffset();
    m_platformManager->update(deltaTime, scrollOffset);
    m_platformManager->resolveCollisions(*m_player);

    m_game.getScoreManager().updateFromHeight(scrollOffset);
    m_hud.setScore(m_game.getScoreManager().getCurrentScore());

    if (isPlayerOutOfBounds())
        triggerGameOver();
}

void GameplayState::render(sf::RenderTarget& target)
{
    m_platformManager->draw(target);
    m_player->draw(target);
    m_hud.draw(target);
}

bool GameplayState::isPlayerOutOfBounds() const
{
    const float windowHeight = static_cast<float>(m_game.getWindow().getSize().y);
    return m_player->getPosition().y > windowHeight;
}

void GameplayState::triggerGameOver()
{
    m_game.getScoreManager().commitIfHighScore();
    m_game.getStateManager().changeState(std::make_unique<GameOverState>(m_game));
}