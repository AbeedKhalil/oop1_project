#pragma once

#include "Consts.h"

struct MenuItem {
    sf::RectangleShape button;
    sf::Text text;
};

class Menu {
private:
    int m_selectedItemIndex;
    sf::Font m_font;
    sf::Font m_menuFont;
    std::vector<MenuItem> m_menuItems;
    static const int m_characterSize = 90;
    static const sf::Color m_normalColor;
    static const sf::Color m_hoverColor;
    static const sf::Color m_textColor;

public:
    Menu();
    void showHelpWindow(sf::RenderWindow& window, GameState& gameState) const;
    void draw(sf::RenderWindow& window);

    void update(sf::RenderWindow& window, GameState& gameState);

    int GetPressedItem() const { return m_selectedItemIndex; }
};