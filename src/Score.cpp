#include "Score.h"

// Constructor
Score::Score() : m_score(0), m_keys(0), m_lives(3) {
    if (!m_font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Green);
    m_background.setSize(sf::Vector2f(310, 30));
    m_background.setFillColor(sf::Color::Black);
    m_background.setPosition(0, 0); // Example position in top left corner
}

// Update the score
void Score::updateScore(int amount, int keys, int lives) {
    m_score = amount;
    m_keys = keys;
    m_lives = lives;
    m_scoreText.setString("Score: " + std::to_string(m_score) + "   Keys: " + std::to_string(m_keys) + "  Lives: " + std::to_string(m_lives));
}

bool Score::youHaveKey() const
{
    return (m_keys > 0);
}

// Render the score on the window
void Score::render(sf::RenderWindow& window) const {
    window.draw(m_background);
    window.draw(m_scoreText);
}