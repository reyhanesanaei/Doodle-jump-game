#pragma once

#include <SFML/Graphics.hpp>

class Game; // forward declaration: full definition only needed in .cpp files

// Abstract base for every game state (Menu, Gameplay, Game Over).
// A concrete state only has to implement these three hooks; the Game Loop
// and StateManager take care of calling them at the right time.
class State
{
public:
    explicit State(Game& game);
    virtual ~State() = default;

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

protected:
    Game& m_game;
};