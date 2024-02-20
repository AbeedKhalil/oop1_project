#include "Score.h"

// Constructor
Score::Score() : m_score(0) {
    if (!m_font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Green);

    m_background.setSize(sf::Vector2f(140, 30));
    m_background.setFillColor(sf::Color::Black);
    m_background.setPosition(0, 0); // Example position in top left corner
}

// Update the score
void Score::updateScore(int amount) {
    m_score = amount;
    m_scoreText.setString("Score: " + std::to_string(m_score));
}

// Render the score on the window
void Score::render(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_scoreText);
}