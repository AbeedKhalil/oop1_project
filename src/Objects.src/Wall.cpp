#include "Wall.h"

Wall::Wall()
{
    initTexture();
    initSprite();
}

Wall::~Wall() {
}

void Wall::initTexture() {
    if (!this->texture.loadFromFile("Wall.png")) {
        std::cout << "ERROR::WALL::INITTEXTURE::Could not load texture file." << std::endl;
    }
}