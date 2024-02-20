#pragma once

#include "Consts.h"
#include "Objects.h"
#include "Wall.h"
#include "Cat.h"
#include "Mouse.h"
#include "RemoveCat.h"
#include "Door.h"
#include "Key.h"
#include "Cheese.h"

class Level {
private:
    sf::RenderWindow& m_window;
    std::vector<std::vector<std::unique_ptr<Objects>>> m_map;
    int m_tileSize, m_level;
    size_t m_cheeseCount;

public:
    Level(sf::RenderWindow& window);
    ~Level() = default; // Compiler-generated destructor is fine if we use smart pointers
    void loadFromFile();
    void updateLevel();
    void updateCheeseNum();
    bool therIsNoCheese() const;
    std::vector<Objects*> getRawObjectPointers() const;
    void render();
};