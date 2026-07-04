#include "Engine/StateManager.hpp"

void StateManager::changeState(std::unique_ptr<State> newState)
{
    m_pendingState = std::move(newState);
    m_hasPendingChange = true;
}

void StateManager::applyPendingChange()
{
    if (m_hasPendingChange)
    {
        m_currentState = std::move(m_pendingState);
        m_hasPendingChange = false;
    }
}

void StateManager::handleEvent(const sf::Event& event)
{
    if (m_currentState)
        m_currentState->handleEvent(event);
}

void StateManager::update(float deltaTime)
{
    applyPendingChange();
    if (m_currentState)
        m_currentState->update(deltaTime);
}

void StateManager::render(sf::RenderTarget& target)
{
    if (m_currentState)
        m_currentState->render(target);
}

bool StateManager::hasState() const
{
    return m_currentState != nullptr;
}
