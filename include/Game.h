#pragma once

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
    int m_scoreAmount, m_keyAmount;

    // Game elements
    std::vector<std::shared_ptr<Objects>> m_sharedObjects;
    sf::Sprite m_spriteGame;
    sf::Sprite m_spriteMenu;
    sf::Texture m_tileSheet;
    sf::Texture m_menuSheet;
    std::unique_ptr<Menu> m_menu;
    std::shared_ptr<Level> m_level;
    sf::Music m_backgroundMusic;

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
    void handleCollisions();

    // Game logic
    void updateGameLogic();
    void playBackgroundMusic(const std::string& filePath);

    // Rendering
    void render();

    // Utility
    void receiveObjectsFromLevel();

public:
    Game();
    virtual ~Game() = default; // Utilize smart pointers, no need for custom destructor

    void run();
};