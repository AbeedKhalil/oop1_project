#include "Key.h"

Key::Key()
{
    initTexture();
    initSprite();
}

void Key::initTexture() {
    if (!this->texture.loadFromFile("Key.png")) {
        // Error handling
        std::cerr << "ERROR::KEY::INITTEXTURE::Could not load texture file." << std::endl;
    }
}