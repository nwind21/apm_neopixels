#include "nw21_types.h"

#ifndef __ISYSTEM
#define __ISYSTEM

class ISystem
{
public:
    virtual ~ISystem() {}

    virtual void sleep( uint32_t val ) = 0;
};

#endif

