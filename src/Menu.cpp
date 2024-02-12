#include "Menu.h"

Menu::Menu() {
    if (!font.loadFromFile("Regular.ttf")) {
        // handle error
    }

    // New Game
    sf::Text newGame("New Game (N)", font);
    newGame.setCharacterSize(24);
    newGame.setFillColor(sf::Color::White);
    newGame.setPosition(sf::Vector2f(105, 0));

    // Help
    sf::Text help("Help (H)", font);
    help.setCharacterSize(24);
    help.setFillColor(sf::Color::White);
    help.setPosition(sf::Vector2f(305, 0));

    // Exit
    sf::Text exit("Exit (E)", font);
    exit.setCharacterSize(24);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(sf::Vector2f(435, 0));

    menuItems.push_back(newGame);
    menuItems.push_back(help);
    menuItems.push_back(exit);

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        window.draw(menuItems[i]);
    }
}

void Menu::MoveRight()
{
}

void Menu::MoveLeft()
{
}
