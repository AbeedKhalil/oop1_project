#pragma once

#include "MovingObjects.h"

class Mouse : public MovingObjects
{
public:
    Mouse();
    virtual ~Mouse() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};