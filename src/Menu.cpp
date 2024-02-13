#include "Menu.h"

Menu::Menu() : selectedItemIndex(0)
{
    if (!font.loadFromFile("Regular.ttf")) {
        std::cerr << "ERROR::CAT::INITFONT::could not load font file.\n";
    }

    sf::Color normalColor = sf::Color{ 200, 200, 200, 192 };
    sf::Color textColor = sf::Color::Black;
    int characterSize = 24;
    std::vector<std::string> labels = { "New (N)", "Help (H)", "Exit (E)" };
    float x = 0.f;
    float buttonWidth = 120.f;
    float buttonHeight = 30.f;

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::RectangleShape shape(sf::Vector2f(buttonWidth, buttonHeight));
        shape.setPosition(x, 0.f); // Set y to 10.f or another fixed value for vertical alignment
        shape.setFillColor(normalColor);

        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(characterSize);
        text.setFillColor(textColor);
        text.setPosition(x + 5.f, 0.f); // Adjust text position relative to its button

        menuButtons.push_back(shape);
        menuTexts.push_back(text);

        x += buttonWidth; // Move x position for the next button
    }

}

void Menu::showHelpWindow() const {
    // Create a new window for help instructions
    sf::RenderWindow helpWindow(sf::VideoMode(300, 300), "How to Play", sf::Style::None);

    sf::Text helpText;
    helpText.setFont(font);
    helpText.setString("How to play:\n Blah Blah...\nHi Roaa!\nPress Esc to Exit...");
    helpText.setCharacterSize(24);
    helpText.setFillColor(sf::Color::Black);
    helpText.setPosition(10.f, 10.f);

    while (helpWindow.isOpen()) {
        sf::Event event;
        while (helpWindow.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    helpWindow.close();
                }
            }
        }

        helpWindow.clear(sf::Color::White);
        helpWindow.draw(helpText);
        helpWindow.display();
    }
}


void Menu::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < menuButtons.size(); ++i) {
        window.draw(menuButtons[i]);
        window.draw(menuTexts[i]);
    }
}

void Menu::update(sf::RenderWindow& window, bool& reset) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < menuButtons.size(); ++i) {
        if (menuButtons[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            menuButtons[i].setFillColor(sf::Color{ 200, 200, 200, 255 }); // Hover color
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (i == 0) {
                    reset = true;
                }
                else if (i == 1) {
                    showHelpWindow(); // Show help window for "Help (H)"
                }
                else if (i == 2) {
                    window.close(); // Close the window for "Exit (E)"
                }
            }
        }
        else {
            menuButtons[i].setFillColor(sf::Color{ 200, 200, 200, 192 }); // Normal color
        }
    }
}

