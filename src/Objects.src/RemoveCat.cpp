#include "RemoveCat.h"

RemoveCat::RemoveCat()
{
    initTexture();
    initSprite();
}

void RemoveCat::initTexture() {
    if (!this->texture.loadFromFile("GiftRemoveCat.png")) {
        // Error handling
        std::cerr << "ERROR::RemoveCat::INITTEXTURE::Could not load texture file." << std::endl;
    }
}