#include "Mouse.h"

Mouse::Mouse() : MovingObjects(1.5f) // Initialize base class members with constructor initializer list
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
			if (!wouldCollide(objects ,mouse, moveX, 0, score)) {
				mouse->move(moveX, 0);
			}
			// Check collision for Y movement
			if (!wouldCollide(objects, mouse, 0, moveY, score)) {
				mouse->move(0, moveY);
			}
		}
	}
}

void Mouse::initTexture()
{
	// Use TextureManager to get the texture instead of loading it directly
	m_texture = TextureManager::getInstance().getTexture("Mouse.png");
}
