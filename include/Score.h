#pragma once

#include "Consts.h"

class Score {
private:
    int m_score, m_keys, m_lives;
    sf::Text m_scoreText;
    sf::Font m_font;
    sf::RectangleShape m_background;

public:
    Score();
    void updateScore(int amount, int keys, int lives);
    bool youHaveKey() const;
    void render(sf::RenderWindow& window) const;
};