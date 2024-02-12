#pragma once

#include "Map.h"
#include "Mouse.h"
#include "Menu.h"
#include "Cat.h"

class Game 
{
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<Objects>> objects;
    sf::Sprite sprite;
    sf::Texture tileSheet;
    Map *map;
    Menu* menu;

    // private functions
    void initWindow();
    void initMenu();
    void initObjects();
    void initTileSheet();
    void initMap();

public:
    Game();
    virtual ~Game();
    void run();
    void updatePollEvent();
    void updateInput();
    void updateMap();
    void renderMap();
    void update();
    void render();
};