#include "Menu.h"

// Define static const colors
const sf::Color Menu::m_normalColor = sf::Color::White;
const sf::Color Menu::m_hoverColor = sf::Color::Yellow;
const sf::Color Menu::m_textColor = sf::Color::White;


Menu::Menu() : m_selectedItemIndex(0) {
    if (!m_font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }
    if (!m_menuFont.loadFromFile("MainMenu.otf")) {
        std::cerr << "ERROR::MENU::Could not load menu font file." << std::endl;
    }

    std::vector<std::string> labels = { "New Game", "    Help", "    Exit" };
    float x = 320.f, y = 170.f; // Starting position for the first button;

    for (const auto& label : labels) {
        MenuItem item;

        item.text.setFont(m_menuFont);
        item.text.setString(label);
        item.text.setCharacterSize(m_characterSize);
        item.text.setFillColor(m_textColor);
        item.text.setPosition(x, y);

        m_menuItems.push_back(item);
        y += 150;
    }
}

void Menu::showHelpWindow(sf::RenderWindow& window, GameState& gameState) const {
    gameState = GameState::Help;

    // Help text setup...
    sf::Text helpText;
    helpText.setFont(m_font);
    helpText.setString("Game Instructions:\n- Use arrow keys to move\n- Press 'E' to exit\n\nGame Objective:\n- Collect all cheese\n- Avoid cats.\n");
    helpText.setCharacterSize(24);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(50.f, 50.f);
    window.draw(helpText);

    // Back button setup
    sf::RectangleShape backButton(sf::Vector2f(50, 25));
    backButton.setPosition(0, 0); // Top left corner
    backButton.setFillColor(m_normalColor);
    window.draw(backButton);

    sf::Text backButtonText;
    backButtonText.setFont(m_font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::Black);
    backButtonText.setPosition(2, 1); // Adjusted for visual alignment
    window.draw(backButtonText);
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : m_menuItems) {
        window.draw(item.button);
        window.draw(item.text);
    }
}
void Menu::update(sf::RenderWindow& window, GameState& gameState) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < m_menuItems.size(); ++i) {
        auto& item = m_menuItems[i];
        if (item.text.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            item.text.setFillColor(m_hoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_selectedItemIndex = static_cast<int>(i);
                switch (i) {
                case 0:  gameState = GameState::InGame; break; // New Game
                case 1: gameState = GameState::Help; break; // Help
                case 2: window.close(); break; // Exit
                }
            }
        }
        else {
            item.text.setFillColor(m_normalColor);
        }
    }

    if (gameState == GameState::Help) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::FloatRect backButtonBounds(0, 0, 50, 25); // Match backButton's size and position

            if (backButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                gameState = GameState::MainMenu; // Change game state to MainMenu
            }
        }
    }

}