#pragma once

#include "Objects.h"
#include "TextureManager.h"

class Key : public Objects {
public:
    Key();
    virtual ~Key() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};