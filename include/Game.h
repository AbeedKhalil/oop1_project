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
    bool m_timer = false;

    // Game elements
    std::vector<std::shared_ptr<Objects>> m_staticObjects;
    std::vector<std::shared_ptr<Objects>> m_movingObjects;
    std::unique_ptr<Menu> m_menu;
    std::unique_ptr<WinMenu> m_winMenu;
    std::shared_ptr<Level> m_level;

    // Texture and sprite assets
    sf::Texture m_tileSheet, m_menuSheet, m_winSheet, m_gameOverSheet;
    sf::Sprite m_spriteGame, m_spriteMenu, m_spriteWin, m_spriteGameOver;

    // Sound assets
    sf::SoundBuffer m_catDies, m_pauseCats, m_timeEnds, m_addTimer, m_unlockDoor;
    sf::Sound m_cat, m_pause, m_time, m_addTime, m_unlock;

    sf::Music m_backgroundMusic;

    // Game control
    bool m_restartGame = false;

    // Initialization
    void initWindow();
    void initMenus();
    void initAssets();
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