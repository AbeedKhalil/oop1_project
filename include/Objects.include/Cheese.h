#pragma once

#include "Objects.h"
#include "TextureManager.h"

class Cheese : public Objects {
public:
    Cheese();
    virtual ~Cheese() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};