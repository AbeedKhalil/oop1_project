#pragma once

#include "Consts.h"

class Score {
private:
    int m_score, m_keys, m_lives, m_level;
    float m_totalGameTime, m_timeLeftForLevel;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Text m_timerText;
    sf::Font m_font;
    sf::RectangleShape m_background;

public:
    Score();
    void updateScore(int amount, int keys, int lives, int level, float currentTime, float gameTime, bool timer);
    bool youHaveKey() const;
    void render(sf::RenderWindow& window) const;
};