#pragma once

#include "Consts.h"

class Score {
private:
    int m_score;
    sf::Text m_scoreText;
    sf::Font m_font;
    sf::RectangleShape m_background;

public:
    Score();
    void updateScore(int amount);
    void render(sf::RenderWindow& window);
};