#pragma once

#include "States/State.hpp"
#include <memory>

// Owns exactly one active State and forwards handleEvent/update/render to it.
// State changes are deferred ("pending") so a state is never destroyed while
// one of its own member functions is still on the call stack — e.g. it is
// safe for GameplayState::update() to call changeState() on itself.
class StateManager
{
public:
    StateManager() = default;

    void changeState(std::unique_ptr<State> newState);

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderTarget& target);

    bool hasState() const;

private:
    void applyPendingChange();

    std::unique_ptr<State> m_currentState;
    std::unique_ptr<State> m_pendingState;
    bool m_hasPendingChange{false};
};