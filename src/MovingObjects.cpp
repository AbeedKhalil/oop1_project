#include "MovingObjects.h"

MovingObjects::MovingObjects(float movingSpeed) : m_movementSpeed(movingSpeed) {}

void MovingObjects::move(float dirX, float dirY)
{
	m_sprite.move(m_movementSpeed * dirX, m_movementSpeed * dirY);
}

float MovingObjects::getMovementSpeed() const
{
	return m_movementSpeed;
}
