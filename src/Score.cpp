#include "Score.h"

// Constructor
Score::Score() : m_score(0), m_keys(0), m_lives(3), m_level(1) {
    if (!m_font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Green);
    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(24);
    m_levelText.setFillColor(sf::Color::Green);
    m_levelText.setPosition(sf::Vector2f(850, 0));
    m_background.setSize(sf::Vector2f(960, 30));
    m_background.setFillColor(sf::Color::Black);
    m_background.setPosition(0, 0); // Example position in top left corner
}

// Update the score
void Score::updateScore(int amount, int keys, int lives, int level) {
    m_score = amount;
    m_keys = keys;
    m_lives = lives;
    m_level = level;
    m_scoreText.setString("Score: " + std::to_string(m_score) + "    Keys: " + std::to_string(m_keys) + "     Lives: " + std::to_string(m_lives));
    m_levelText.setString("LEVEL: " + std::to_string(m_level));
}

bool Score::youHaveKey() const
{
    return (m_keys > 0);
}

// Render the score on the window
void Score::render(sf::RenderWindow& window) const {
    window.draw(m_background);
    window.draw(m_scoreText);
    window.draw(m_levelText);
}