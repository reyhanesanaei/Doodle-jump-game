#include "States/GameplayState.hpp"

#include "Engine/Game.hpp"

#include <algorithm>
#include <stdexcept>

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
          game.textures().get("player_right"),
          game.textures().get("shooting_doodle"),
          game.textures().get("Nose")),
      m_platforms(
          game.textures().get("platform_normal"),
          game.textures().get("platform_moving"),
          game.textures().get("platform_breakable"),
          game.textures().get("spring")),
    m_hud(game.fonts().get("main")),
    m_shootSound(m_shootBuffer),
    m_jumpSound(m_jumpBuffer)
{
    fitToWindow(m_background);

    m_monsterSpawnY = 600.f;

    m_hud.update(
        m_game.scores().currentScore(),
        m_game.scores().highScore()
    );

    if (!m_shootBuffer.loadFromFile("sounds/shooting_Sound.wav"))
    {
        throw std::runtime_error("Couldn't load shooting sound.");
    }

    m_shootSound = sf::Sound(m_shootBuffer);


    if (!m_jumpBuffer.loadFromFile("sounds/Jumping_Sound.wav"))
    {
        throw std::runtime_error("Couldn't load jump sound.");
    }

    m_jumpSound = sf::Sound(m_jumpBuffer);


}

void GameplayState::handleEvent(const sf::Event&)
{
}

void GameplayState::update(float dt)
{
    m_shootCooldown -= dt;

    m_player.update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
        m_shootCooldown <= 0.f)
    {
        sf::Vector2f spawnPos = m_player.getPosition();

        if (m_player.isFacingRight())
            spawnPos.x += 28.f;
        else
            spawnPos.x += 8.f;

        spawnPos.y -= 18.f;

        m_bullets.emplace_back(
            spawnPos,
            m_player.isFacingRight()
        );

        m_shootSound.play();

        m_shootCooldown = 0.2f;
    }

    m_platforms.update(dt);

    m_monsters.update(dt);

    for (auto& monster : m_monsters.monsters())
    {
        if (monster.isDead() ||
            !m_player.getBounds().findIntersection(monster.getBounds()))
            continue;

        const auto current = m_player.getBounds();
        const auto previous = m_player.getPreviousBounds();
        const auto enemy = monster.getBounds();

        const bool stompedFromAbove =
            m_player.isFalling() &&
            previous.position.y + previous.size.y <= enemy.position.y + 18.f &&
            current.position.y + current.size.y >= enemy.position.y;

        if (stompedFromAbove)
        {
            monster.takeDamage();
            m_player.jump();
        }
        else
        {
            m_game.showGameOver();
            break;
        }
    }

    auto& monsters = m_monsters.monsters();

    monsters.erase(
        std::remove_if(
            monsters.begin(),
            monsters.end(),
            [](const Monster& monster)
            {
                return monster.isDead();
            }),
        monsters.end()
    );


    if(Spring* spring = m_collisions.findLandedSpring(m_player, m_platforms))
    {
        m_player.springJump();
        spring->deactivate();
        m_jumpSound.play();
    }
    else if(Platform* platform = m_collisions.findLandedPlatform(m_player, m_platforms))
    {
        platform->onPlayerLanded(m_player);
        m_jumpSound.play();
    }

    constexpr float CameraLockY = 360.f;

    if(m_player.getY() < CameraLockY)
    {
        const float offset = CameraLockY - m_player.getY();

        m_player.move(offset);
        m_platforms.scroll(offset);
        m_monsters.move(offset);

        m_game.scores().addHeight(offset);
    }

    m_platforms.removeOld(static_cast<float>(Game::WindowHeight));
    m_platforms.ensurePlatforms();
        if (m_game.scores().currentScore() > m_monsterSpawnY)
    {
        m_monsterSpawnY += 500.f;

        auto& platforms = m_platforms.platforms();

        if (!platforms.empty())
        {
            sf::FloatRect bounds;

            do
            {
                int index = rand() % platforms.size();
                bounds = platforms[index]->getBounds();

            } while (bounds.position.y > -100.f ||
                     bounds.position.y < -500.f);


            MonsterType type =
                (rand() % 2 == 0)
                ? MonsterType::Blue
                : MonsterType::Green;


            if (type == MonsterType::Blue)
            {
                m_monsters.addMonster(
                    m_game.textures().get("blueMonster"),
                    {bounds.position.x, bounds.position.y - 60.f},
                    MonsterType::Blue
                );
            }
            else
            {
                m_monsters.addMonster(
                    m_game.textures().get("greenMonster"),
                    {bounds.position.x, bounds.position.y - 60.f},
                    MonsterType::Green
                );
            }
        }
    }


    m_hud.update(
        m_game.scores().currentScore(),
        m_game.scores().highScore()
    );


    for (auto& bullet : m_bullets)
    {
        bullet.update(dt);

        for (auto& monster : m_monsters.monsters())
        {
            if (!bullet.getBounds().findIntersection(monster.getBounds()))
                continue;

            bullet.destroy();
            monster.takeDamage();
            break;
        }
    }


    m_bullets.erase(
        std::remove_if(
            m_bullets.begin(),
            m_bullets.end(),
            [](const Bullet& bullet)
            {
                return bullet.isOffScreen() || bullet.isDestroyed();
            }),
        m_bullets.end()
    );


    if(m_player.getY() > static_cast<float>(Game::WindowHeight) + 80.f)
    {
        m_game.showGameOver();
    }
}


void GameplayState::render(sf::RenderWindow& window)
{
    window.draw(m_background);

    m_platforms.draw(window);

    m_monsters.draw(window);


    for (const auto& bullet : m_bullets)
    {
        bullet.draw(window);
    }


    m_player.draw(window);

    m_hud.draw(window);
}


void GameplayState::spawnMonster(sf::Vector2f position, MonsterType type)
{
    m_monsters.spawnOnPlatforms(
        m_platforms,
        m_game.textures().get("blueMonster"),
        m_game.textures().get("greenMonster")
    );
}