#include "Engine/StateManager.hpp"

void StateManager::changeState(std::unique_ptr<IState> state)
{
    m_pendingState = std::move(state);
}

void StateManager::applyPendingState()
{
    if(m_pendingState)
        m_currentState = std::move(m_pendingState);
}

void StateManager::handleEvent(const sf::Event& event)
{
    applyPendingState();

    if(m_currentState)
        m_currentState->handleEvent(event);

    applyPendingState();
}

void StateManager::update(float dt)
{
    applyPendingState();

    if(m_currentState)
        m_currentState->update(dt);

    applyPendingState();
}

void StateManager::render(sf::RenderWindow& window)
{
    applyPendingState();

    if(m_currentState)
        m_currentState->render(window);
}
