#pragma once

#include "Objects.h"

class MovingObjects : public Objects
{
public:
	// Constructor
	MovingObjects(float movingSpeed);

	// Virtual Destructor
	virtual ~MovingObjects() = default;

    // Functions
    virtual void move(float dirX, float dirY);
    float getMovementSpeed() const;

	bool wouldCollide(std::vector<std::shared_ptr<Objects>> objects, Objects* obj, float moveX, float moveY, Score score);
	bool checkCollision(std::vector<std::shared_ptr<Objects>> objects, Objects* obj, float moveX, float moveY, Score score);

protected:
    float m_movementSpeed;
};