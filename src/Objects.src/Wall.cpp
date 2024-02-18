#include "Wall.h"

Wall::Wall()
{
    this->m_size = 60.f;
    initTexture();
    initSprite();
}

void Wall::initTexture() {
    if (!this->m_texture.loadFromFile("Wall.png")) {
        // Error handling
        std::cerr << "ERROR::WALL::INITTEXTURE::Could not load texture file." << std::endl;
    }
}