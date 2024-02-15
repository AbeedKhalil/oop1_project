#include "Cheese.h"

Cheese::Cheese()
{
    initTexture();
    initSprite(); // Assuming initSprite() is suitable without modifications
}

void Cheese::initTexture() {
    if (!this->texture.loadFromFile("Cheese.png")) {
        // Error handling
        std::cerr << "ERROR::CHEESE::INITTEXTURE::Could not load texture file." << std::endl;
    }
}