#pragma once

#include "Menu.h"
#include "WinMenu.h"
#include "Level.h"

class Game {
private:
    // Window
    std::unique_ptr<sf::RenderWindow> m_window;

    // Game State
    GameState m_gameState;

    // score
    Score m_score;
    int m_scoreAmount, m_keyAmount, m_livesAmount, m_levelNum;

    // timer
    sf::Clock clock;
    float m_timeLimit; // Time limit for the level in seconds
    float m_currentTime; // Current time left in the level
    float m_totalGameTime;
    float m_catPauseTime = 0.0f;

    // Game elements
    std::vector<std::shared_ptr<Objects>> m_sharedObjects;
    sf::Sprite m_spriteGame;
    sf::Sprite m_spriteMenu;
    sf::Sprite m_spriteWin;
    sf::Sprite m_spriteGameOver;
    sf::Texture m_tileSheet;
    sf::Texture m_menuSheet;
    sf::Texture m_winSheet;
    sf::Texture m_gameOverSheet;
    std::unique_ptr<Menu> m_menu;
    std::unique_ptr<WinMenu> m_winMenu;
    std::shared_ptr<Level> m_level;
    sf::Music m_backgroundMusic;

    // Game control
    bool m_restartGame = false;

    // Initialization
    void initWindow();
    void initMenu();
    void initWinMenu();
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