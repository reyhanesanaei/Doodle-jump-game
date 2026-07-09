#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

class IState
{
public:
    virtual ~IState() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class StateManager
{
public:
    void changeState(std::unique_ptr<IState> state);
    void applyPendingState();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    std::unique_ptr<IState> m_currentState;
    std::unique_ptr<IState> m_pendingState;
};
