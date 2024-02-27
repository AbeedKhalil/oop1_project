#include "WinMenu.h"

// Define static const colors
const sf::Color WinMenu::m_normalColor = sf::Color::Black;
const sf::Color WinMenu::m_hoverColor = sf::Color(40, 50, 60);
const sf::Color WinMenu::m_textColor = sf::Color::Black;


WinMenu::WinMenu() : m_selectedItemIndex(0) {
    if (!m_font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }
    if (!m_menuFont.loadFromFile("MainMenu.otf")) {
        std::cerr << "ERROR::MENU::Could not load menu font file." << std::endl;
    }

    std::vector<std::string> labels = { "New Game", "    Exit" };
    float x = 250.f, y = 160.f; // Starting position for the first button;

    for (const auto& label : labels) {
        WinItem item{};
        item.text.setFont(m_menuFont);
        item.text.setString(label);
        item.text.setCharacterSize(m_characterSize);
        item.text.setFillColor(m_textColor);
        item.text.setPosition(x, y);

        m_menuItems.push_back(item);
        y += 180;
    }
}

void WinMenu::draw(sf::RenderWindow& window) {
    for (const auto& item : m_menuItems) {
        window.draw(item.text);
    }
}
void WinMenu::update(sf::RenderWindow& window, GameState& gameState) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < m_menuItems.size(); ++i) {
        auto& item = m_menuItems[i];
        if (item.text.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            item.text.setFillColor(m_hoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_selectedItemIndex = static_cast<int>(i);
                switch (i) {
                case 0:  gameState = GameState::InGame; break; // New Game
                case 1: window.close(); break; // Exit
                }
            }
        }
        else {
            item.text.setFillColor(m_normalColor);
        }
    }
}