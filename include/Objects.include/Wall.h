#pragma once

#include "Objects.h"
#include "TextureManager.h"

class Wall : public Objects {
public:
    Wall();
    virtual ~Wall() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};