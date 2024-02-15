#include "Wall.h"

Wall::Wall()
{
    this->size = 60.f;
    initTexture();
    initSprite();
}

void Wall::initTexture() {
    if (!this->texture.loadFromFile("Wall.png")) {
        // Error handling
        std::cerr << "ERROR::WALL::INITTEXTURE::Could not load texture file." << std::endl;
    }
}