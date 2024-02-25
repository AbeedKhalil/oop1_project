#include "MovingObjects.h"
#include "Wall.h"
#include "Door.h"

MovingObjects::MovingObjects(float movingSpeed) : m_movementSpeed(movingSpeed) {}

void MovingObjects::move(float dirX, float dirY)
{
	m_sprite.move(m_movementSpeed * dirX, m_movementSpeed * dirY);
}

float MovingObjects::getMovementSpeed() const
{
	return m_movementSpeed;
}

bool MovingObjects::wouldCollide(std::vector<std::shared_ptr<Objects>> objects, Objects* obj, float moveX, float moveY, Score score)
{
	// Calculate the proposed new bounding box for obj after moving
	sf::FloatRect nextPos(obj->getPosition().x + moveX, obj->getPosition().y + moveY, obj->getBounds().width + 1, obj->getBounds().height + 1);

	// Check against all wall objects
	for (auto& wallObj : objects) {
		Wall* wall = dynamic_cast<Wall*>(wallObj.get());
		if (wall) {
			sf::FloatRect wallBounds = wall->getBounds();
			if (nextPos.intersects(wallBounds)) {
				return true; // Collision detected
			}
		}
	}
	// Check against all door objects
	for (auto& doorObj : objects) {
		Door* door = dynamic_cast<Door*>(doorObj.get());
		if (door && door->isVisible() && !score.youHaveKey()) {
			sf::FloatRect doorBounds = door->getBounds();
			if (nextPos.intersects(doorBounds)) {
				return true; // Collision detected
			}
		}
	}
	return false; // No collision detected
}

bool MovingObjects::checkCollision(std::vector<std::shared_ptr<Objects>> objects, Objects* obj, float moveX, float moveY, Score score)
{
	// Iterate over all objects to find walls
	for (auto& wallObj : objects) {
		Wall* wall = dynamic_cast<Wall*>(wallObj.get());
		if (wall) {
			if (wouldCollide(objects, obj, moveX, moveY, score)) {
				return true; // Collision detected
			}
		}
	}
	// Iterate over all objects to find doors
	for (auto& doorObj : objects) {
		Door* door = dynamic_cast<Door*>(doorObj.get());
		if (door) {
			if (wouldCollide(objects, obj, moveX, moveY, score)) {
				return true; // Collision detected
			}
		}
	}
	return false; // No collision detected
}
