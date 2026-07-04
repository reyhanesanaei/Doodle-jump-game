#include "States/State.hpp"
#include "UI/HUD.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Player and PlatformManager belong to the Entities/ and Managers/ sections
// (not part of this batch of files). GameplayState only needs to know that
// they exist and what their public interface looks like — see the comment
// block at the top of GameplayState.cpp for the exact methods it calls.
class Player;
class PlatformManager;

// The core gameplay loop: drives the player, the scrolling world of
// platforms, the live score, and detects the "fell off the bottom of the
// screen" condition that ends the run.
class GameplayState : public State
{
public:
    explicit GameplayState(Game& game);
    ~GameplayState() override;

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;

private:
    bool isPlayerOutOfBounds() const;
    void triggerGameOver();

    std::unique_ptr<Player> m_player;
    std::unique_ptr<PlatformManager> m_platformManager;
    HUD m_hud;
};