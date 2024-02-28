#pragma once

#include "Consts.h"
#include "Wall.h"
#include "Heart.h"
#include "Cat.h"
#include "Mouse.h"
#include "RemoveCat.h"
#include "Door.h"
#include "AddTime.h"
#include "Key.h"
#include "PuseCats.h"
#include "Cheese.h"

class Level {
private:
    sf::RenderWindow& m_window;
    std::vector<std::vector<std::shared_ptr<Objects>>> m_static;
    std::vector<std::vector<std::shared_ptr<Objects>>> m_moving;
    int m_tileSize, m_level;
    size_t m_cheeseCount;
    bool m_timerOn = false;

public:
    Level(sf::RenderWindow& window);
    ~Level() = default; // Compiler-generated destructor is fine if we use smart pointers
    void loadFromFile();
    void resetMoving();
    void updateLevel(GameState& gameState);
    void updateCheeseNum();
    bool therIsNoCheese() const;
    std::vector<sf::Vector2f> initialMovingPositions;
    std::vector<std::shared_ptr<Objects>> getStaticObjectPointers(bool& timer) const;
    std::vector<std::shared_ptr<Objects>> getMovingObjectPointers() const;
    void render();
};