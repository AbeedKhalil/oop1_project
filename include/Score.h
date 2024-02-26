#pragma once

#include "Consts.h"

class Score {
private:
    int m_score, m_keys, m_lives, m_level;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Font m_font;
    sf::RectangleShape m_background;

public:
    Score();
    void updateScore(int amount, int keys, int lives, int level);
    bool youHaveKey() const;
    void render(sf::RenderWindow& window) const;
};