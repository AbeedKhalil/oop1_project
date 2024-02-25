#pragma once

#include "Objects.h"
#include "TextureManager.h"

class Door : public Objects 
{
public:
    Door();
    virtual ~Door() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};
