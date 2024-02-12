#include "Cheese.h"

Cheese::Cheese()
{
    initTexture();
    initSprite(); // Assuming initSprite() is suitable without modifications
}

Cheese::~Cheese() {
}

void Cheese::initTexture() {
    if (!this->texture.loadFromFile("Cheese.png")) {
        std::cout << "ERROR::CHEESE::INITTEXTURE::Could not load texture file." << std::endl;
    }
}