#include "Key.h"

Key::Key()
{
    initTexture();
    initSprite();
}

Key::~Key() {
}

void Key::initTexture() {
    if (!this->texture.loadFromFile("Key.png")) {
        std::cout << "ERROR::KEY::INITTEXTURE::Could not load texture file." << std::endl;
    }
}