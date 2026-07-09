#pragma once

#include <string>

class ScoreManager
{
public:
    explicit ScoreManager(std::string highScoreFile);

    void resetCurrent();
    void addHeight(float height);
    void finishRun();

    int currentScore() const;
    int highScore() const;

private:
    void loadHighScore();
    void saveHighScore() const;

    std::string m_highScoreFile;
    int m_currentScore = 0;
    int m_highScore = 0;
};
