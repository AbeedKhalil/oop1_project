#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuTexts;
    std::vector<sf::RectangleShape> menuButtons;

public:
    Menu();

    void showHelpWindow() const;
    void draw(sf::RenderWindow& window);
    //void MoveRight();
    //void MoveLeft();
    void update(sf::RenderWindow& window, bool& reset);
    int GetPressedItem() const { return selectedItemIndex; }
};
