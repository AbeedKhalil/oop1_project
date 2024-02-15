#pragma once

#include "Menu.h"
#include "Level.h"

class Game {
private:
    // Window
    std::unique_ptr<sf::RenderWindow> window;

    // Game State
    GameState gameState;

    // Game elements
    std::vector<std::unique_ptr<Objects>> objects;
    sf::Sprite spriteGame;
    sf::Sprite spriteMenu;
    sf::Texture tileSheet;
    sf::Texture menuSheet;
    std::unique_ptr<Menu> menu;
    std::unique_ptr<Level> level;

    // Game control
    bool restartGame = false;

    // Initialization
    void initWindow();
    void initMenu();
    void initTileSheet();
    void initLevel();

    // Event handling
    void pollEvents();
    void updateInput();

    // Game logic
    void updateGameLogic();

    // Rendering
    void render();

    // Utility
    void receiveObjectsFromLevel();
    bool wouldCollide(Objects* obj, float moveX, float moveY);
    bool checkCollisionWithWalls(Objects* obj, float moveX, float moveY);

public:
    Game();
    virtual ~Game() = default; // Utilize smart pointers, no need for custom destructor

    void run();
};
