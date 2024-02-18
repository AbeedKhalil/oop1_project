#pragma once

#include "Menu.h"
#include "Level.h"

class Game {
private:
    // Window
    std::unique_ptr<sf::RenderWindow> m_window;

    // Game State
    GameState m_gameState;

    // Game elements
    std::vector<std::unique_ptr<Objects>> m_objects;
    sf::Sprite m_spriteGame;
    sf::Sprite m_spriteMenu;
    sf::Texture m_tileSheet;
    sf::Texture m_menuSheet;
    std::unique_ptr<Menu> m_menu;
    std::unique_ptr<Level> m_level;

    // Game control
    bool m_restartGame = false;

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