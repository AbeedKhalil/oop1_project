#pragma once

#include "Tile.h"

class Map
{
private:
    std::vector< std::vector<Tile*> > tiles;
    sf::Texture* tileSheet;
    unsigned tileSize;

public:
    Map();
    Map(unsigned width, unsigned height, sf::Texture* tileSheet, unsigned tileSize);
    ~Map();

    // functions
    void addTile(unsigned x, unsigned y);
    void removeTile(unsigned x, unsigned y);

    void update();
    void render(sf::RenderTarget& target);
};
