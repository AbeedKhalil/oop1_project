#pragma once

#include "Objects.h"
#include "Score.h"

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

	bool wouldCollide(const std::vector<std::shared_ptr<Objects>>& objects, Objects* obj, float moveX, float moveY, const Score& score);

protected:
    float m_movementSpeed;
};