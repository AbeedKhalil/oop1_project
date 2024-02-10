#pragma once

#include "Consts.h"
#include <iostream>
#include <fstream>
#include <filesystem> // For checking file existence
#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
private:
    int m_level;
    std::vector<std::vector<char>> m_map;
    std::vector<std::vector<sf::Sprite>> tiles; // 2D vector for map tiles
    sf::Texture tileTexture; // Texture for the tiles

    void initTiles(); // Initialize the tiles based on the level data

    sf::Texture wallTexture;
    sf::Texture mouseTexture;

public:
    Map();
    ~Map();

    void preloadTextures();

    void loadLevel();
    void render(sf::RenderTarget& target);

    void updateLevel();

    bool readLevelFromFile(const int level);
};
