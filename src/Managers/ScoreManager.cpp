#include "Managers/ScoreManager.hpp"

#include <algorithm>
#include <fstream>
#include <utility>

ScoreManager::ScoreManager(std::string highScoreFile)
    : m_highScoreFile(std::move(highScoreFile))
{
    loadHighScore();
}

void ScoreManager::resetCurrent()
{
    m_currentScore = 0;
}

void ScoreManager::addHeight(float height)
{
    m_currentScore += std::max(0, static_cast<int>(height));
}

void ScoreManager::finishRun()
{
    if(m_currentScore > m_highScore)
    {
        m_highScore = m_currentScore;
        saveHighScore();
    }
}

int ScoreManager::currentScore() const
{
    return m_currentScore;
}

int ScoreManager::highScore() const
{
    return m_highScore;
}

void ScoreManager::loadHighScore()
{
    std::ifstream input(m_highScoreFile);
    if(input)
        input >> m_highScore;
}

void ScoreManager::saveHighScore() const
{
    std::ofstream output(m_highScoreFile, std::ios::trunc);
    output << m_highScore << '\n';
}
