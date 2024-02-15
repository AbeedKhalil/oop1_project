#pragma once

#include "Consts.h"

struct MenuItem {
    sf::RectangleShape button;
    sf::Text text;
};

class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<MenuItem> menuItems;
    static const int characterSize = 33;
    static const sf::Color normalColor;
    static const sf::Color hoverColor;
    static const sf::Color textColor;

public:
    Menu();
    void showHelpWindow(sf::RenderWindow& window, GameState& gameState) const;
    void draw(sf::RenderWindow& window);

    void update(sf::RenderWindow& window, GameState& gameState);

    int GetPressedItem() const { return selectedItemIndex; }
};