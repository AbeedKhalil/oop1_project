#pragma once

#include "Objects.h"

class Key : public Objects {
public:
    Key();
    virtual ~Key();

protected:
    void initTexture() override;
};