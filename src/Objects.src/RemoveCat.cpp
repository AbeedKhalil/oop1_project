#include "RemoveCat.h"

RemoveCat::RemoveCat()
{
    initTexture();
    initSprite();
}

RemoveCat::~RemoveCat() {
}

void RemoveCat::initTexture() {
    if (!this->texture.loadFromFile("GiftRemoveCat.png")) {
        std::cout << "ERROR::RemoveCat::INITTEXTURE::Could not load texture file." << std::endl;
    }
}