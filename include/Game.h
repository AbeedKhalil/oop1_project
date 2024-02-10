#pragma once

#include "Map.h"
#include "Mouse.h"
#include "Cat.h"
#include <memory>
#include <vector>

class Game 
{
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<Objects>> objects;
    Map levelMap;

    void initWindow();
    void initObjects();
    void updatePollEvent();
    void updateInput();
    void update();
    void render();

public:
    Game();
    virtual ~Game();
    void run();
};