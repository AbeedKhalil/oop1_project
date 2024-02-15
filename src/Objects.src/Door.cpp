#include "Door.h"

Door::Door()
{
    this->size = 60.f;
    initTexture();
    initSprite();
}

void Door::initTexture() {
    if (!this->texture.loadFromFile("Door.png")) {
        // Error handling
        std::cerr << "ERROR::DOOR::INITTEXTURE::Could not load texture file." << std::endl;
    }
}