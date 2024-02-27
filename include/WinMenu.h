#pragma once

#include "Consts.h"

struct WinItem {
    sf::Text text;
};

class WinMenu {
private:
    int m_selectedItemIndex;
    sf::Font m_font;
    sf::Font m_menuFont;
    std::vector<WinItem> m_menuItems;
    static const int m_characterSize = 120;
    static const sf::Color m_normalColor;
    static const sf::Color m_hoverColor;
    static const sf::Color m_textColor;

public:
    WinMenu();
    void draw(sf::RenderWindow& window);

    void update(sf::RenderWindow& window, GameState& gameState);

    int GetPressedItem() const { return m_selectedItemIndex; }
};