#include "Cat.h"

Cat::Cat() : Objects(2.f, 45.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Cat::initTexture()
{
    if (!texture.loadFromFile("SmartCat.png")) {
        // Error handling
        std::cerr << "ERROR::CAT::Could not load texture file." << std::endl;
    }
}