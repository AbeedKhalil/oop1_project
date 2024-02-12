#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu();
    ~Menu();

    void draw(sf::RenderWindow& window);
    void MoveRight();
    void MoveLeft();
    int GetPressedItem() const { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};
