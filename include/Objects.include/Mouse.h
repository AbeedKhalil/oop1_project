#pragma once

#include "Objects.h"

class Mouse : public Objects
{
public:
    Mouse();
    virtual ~Mouse() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};