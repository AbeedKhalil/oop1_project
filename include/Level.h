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

class Level
{
private:
    sf::RenderWindow& window;
    std::vector<std::vector<Objects*>> map;
    int tileSize;

public:
    Level(sf::RenderWindow& window);
    ~Level();
    std::vector<Objects*> getRawObjectPointers() const;
    void loadFromFile();
    void render();
};