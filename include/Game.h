#pragma once

#include "Map.h"
#include "Mouse.h"
#include "Cat.h"

class Game 
{
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<Objects>> objects;
    sf::Texture tileSheet;
    Map *map;

    // private functions
    void initWindow();
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