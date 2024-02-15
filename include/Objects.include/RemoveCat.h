#pragma once

#include "Objects.h"

class RemoveCat : public Objects {
public:
    RemoveCat();
    virtual ~RemoveCat() = default; // Use compiler-generated destructor

protected:
    void initTexture() override;
};
