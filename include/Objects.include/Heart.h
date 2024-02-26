#pragma once

#include "Objects.h"
#include "TextureManager.h"

class Heart : public Objects {
public:
    Heart();
    virtual ~Heart() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};