#include "Mouse.h"

Mouse::Mouse() : MovingObjects(3.f) // Initialize base class members with constructor initializer list
{
    initTexture();
    initSprite();
}

void Mouse::moveMouse(std::vector<std::shared_ptr<Objects>> objects, float moveX, float moveY, Score score)
{
	for (auto& obj : objects) {
		Mouse* mouse = dynamic_cast<Mouse*>(obj.get()); // Try to cast to Mouse*
		if (mouse) // If it's a Mouse
		{
			// Check collision for X movement
			if (!checkCollision(objects ,mouse, moveX, 0, score)) {
				mouse->move(moveX, 0);
			}
			// Check collision for Y movement
			if (!checkCollision(objects, mouse, 0, moveY, score)) {
				mouse->move(0, moveY);
			}
		}
	}
}

void Mouse::initTexture()
{
    if (!this->m_texture.loadFromFile("Mouse.png"))
    {
        // Error handling
        std::cerr << "ERROR::MOUSE::INITTEXTURE::could not load texture file.\n";
    }
}
