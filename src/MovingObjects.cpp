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

bool MovingObjects::wouldCollide(const std::vector<std::shared_ptr<Objects>>& objects, Objects* obj, float moveX, float moveY, const Score& score)
{
    sf::FloatRect nextPos(obj->getPosition().x + moveX, obj->getPosition().y + moveY, obj->getBounds().width + 1, obj->getBounds().height + 1);

    for (const auto& object : objects) {
        if (auto wall = dynamic_cast<Wall*>(object.get())) {
            if (nextPos.intersects(wall->getBounds())) {
                return true; // Wall collision detected
            }
        }
        else if (auto door = dynamic_cast<Door*>(object.get())) {
            if (door->isVisible() && !score.youHaveKey() && nextPos.intersects(door->getBounds())) {
                return true; // Door collision detected
            }
        }
    }
    return false; // No collision detected
}
