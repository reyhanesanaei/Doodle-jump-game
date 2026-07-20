#pragma once

#include "Engine/StateManager.hpp"
#include "Entities/Player.hpp"
#include "Managers/MonsterManager.hpp"
#include "Entities/Monster.hpp"
#include "Bullets/Bullet.hpp"
#include "Managers/CollisionManager.hpp"
#include "Managers/PlatformManager.hpp"
#include "UI/HUD.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

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
    //phase2
    std::vector<Bullet> m_bullets;
    MonsterManager m_monsters; 
    void spawnMonster(sf::Vector2f position, MonsterType type);
    float m_shootCooldown = 0.f;
    float m_monsterSpawnY = 350.f; 

    sf::SoundBuffer m_shootBuffer;
    sf::Sound m_shootSound;

    sf::SoundBuffer m_jumpBuffer;
    sf::Sound m_jumpSound;

};
