#include "Cat.h"

Cat::Cat() : MovingObjects(2.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Cat::initTexture()
{
    if (!m_texture.loadFromFile("SmartCat.png")) {
        // Error handling
        std::cerr << "ERROR::CAT::Could not load texture file." << std::endl;
    }
}