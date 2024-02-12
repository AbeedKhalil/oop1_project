#include "Door.h"

Door::Door()
{
    initTexture();
    initSprite();
}

Door::~Door() {
}

void Door::initTexture() {
    if (!this->texture.loadFromFile("Door.png")) {
        std::cout << "ERROR::DOOR::INITTEXTURE::Could not load texture file." << std::endl;
    }
}