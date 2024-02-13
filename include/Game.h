#pragma once

#include "Menu.h"
#include "Level.h"

class Game
{
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<Objects>> objects;
    sf::Sprite sprite;
    sf::Texture tileSheet;
    Menu* menu;
    Level* level;
    bool restartGame = false;

    // private functions
    void initWindow();
    void initMenu();
    void initTileSheet();

public:
    Game();
    virtual ~Game();
    void run();
    void receiveObjectsFromLevel(const std::vector<Objects*>& rawObjects);
    void updatePollEvent();
    void updateInput();
    void update();
    void render();
};