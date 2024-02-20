#pragma once

#include "Score.h"
#include "Menu.h"
#include "Level.h"

class Game {
private:
    // Window
    std::unique_ptr<sf::RenderWindow> m_window;

    // Game State
    GameState m_gameState;

    // score
    Score m_score;
    int m_scoreAmount;

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
    void displayStartupImage();

    // Event handling
    void pollEvents();
    void updateInput();

    // Game logic
    void updateGameLogic();
    std::vector<sf::Vector2f> alternativeDirections = {
    {0, 1},  // Down
    {1, 0},  // Right
    {0, -1}, // Up
    {-1, 0}  // Left
    };

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