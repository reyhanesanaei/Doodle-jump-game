#pragma once

#include "Engine/StateManager.hpp"
#include "Entities/Player.hpp"
#include "Managers/CollisionManager.hpp"
#include "Managers/PlatformManager.hpp"
#include "UI/HUD.hpp"

#include <SFML/Graphics.hpp>

class Game;

class GameplayState : public IState
{
public:
    explicit GameplayState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    Game& m_game;
    sf::Sprite m_background;
    Player m_player;
    PlatformManager m_platforms;
    CollisionManager m_collisions;
    HUD m_hud;
};
