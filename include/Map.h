#pragma once

#include "Tile.h"

class Map
{
private:
    std::vector< std::vector<Tile*> > tiles;
    sf::Texture* tileSheet;
    unsigned tileSize;

    // Textures
    sf::Texture* wallTexture;
    sf::Texture* mouseTexture;
    sf::Texture* catTexture;
    sf::Texture* cheeseTexture;
    sf::Texture* doorTexture;
    sf::Texture* keyTexture;
    sf::Texture* giftTexture;
    sf::Texture* tileTexture;

    void preloadTextures();

public:
    Map();
    Map(unsigned width, unsigned height, sf::Texture* tileSheet, unsigned tileSize);
    ~Map();

    // functions
    void addTile(unsigned x, unsigned y, sf::IntRect textureRect, bool damaging);
    void removeTile(unsigned x, unsigned y);

    void loadFromFile();

    void update();
    void render(sf::RenderTarget& target);
};