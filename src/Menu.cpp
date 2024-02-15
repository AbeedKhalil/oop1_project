#include "Menu.h"

// Define static const colors
const sf::Color Menu::normalColor = sf::Color{ 200, 200, 200, 150 };
const sf::Color Menu::hoverColor = sf::Color{ 200, 200, 200, 255 };
const sf::Color Menu::textColor = sf::Color::Black;


Menu::Menu() : selectedItemIndex(0) {
    if (!font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::MENU::Could not load font file." << std::endl;
    }

    std::vector<std::string> labels = { "New Game", "      Help", "       Exit" };
    float x = 350.f, y = 200.f; // Starting position for the first button
    float buttonWidth = 250.f, buttonHeight = 80.f;

    for (const auto& label : labels) {
        MenuItem item;
        item.button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        item.button.setPosition(x, y);
        item.button.setFillColor(normalColor);

        item.text.setFont(font);
        item.text.setString(label);
        item.text.setCharacterSize(characterSize);
        item.text.setFillColor(textColor);
        item.text.setPosition(x + 30.f, y + 25); // Slight offset for better visual alignment

        menuItems.push_back(item);
        y += buttonHeight + 20; // Increment y position for next button
    }
}

void Menu::showHelpWindow(sf::RenderWindow& window, GameState& gameState) const {
    gameState = GameState::Help;

    // Help text setup...
    sf::Text helpText;
    helpText.setFont(font);
    helpText.setString("Game Instructions:\n- Use arrow keys to move\n- Press 'E' to exit\n\nGame Objective:\n- Collect all cheese\n- Avoid cats.\n");
    helpText.setCharacterSize(24);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(50.f, 50.f);
    window.draw(helpText);

    // Back button setup
    sf::RectangleShape backButton(sf::Vector2f(50, 25));
    backButton.setPosition(0, 0); // Top left corner
    backButton.setFillColor(normalColor);
    window.draw(backButton);

    sf::Text backButtonText;
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::Black);
    backButtonText.setPosition(2, 1); // Adjusted for visual alignment
    window.draw(backButtonText);
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item.button);
        window.draw(item.text);
    }
}
void Menu::update(sf::RenderWindow& window, GameState& gameState) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < menuItems.size(); ++i) {
        auto& item = menuItems[i];
        if (item.button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            item.button.setFillColor(hoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                selectedItemIndex = static_cast<int>(i);
                switch (i) {
                case 0:  gameState = GameState::InGame; break; // New Game
                case 1: gameState = GameState::Help; break; // Help
                case 2: window.close(); break; // Exit
                }
            }
        }
        else {
            item.button.setFillColor(normalColor);
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