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

protected:
    float m_movementSpeed;
};