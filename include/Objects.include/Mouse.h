#pragma once

#include "Objects.h"

class Mouse : public Objects
{
public:
    Mouse();
    virtual ~Mouse();

protected:
    void initTexture() override;
};