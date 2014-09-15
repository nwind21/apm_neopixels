#include "nw21_types.h"
#include "ISystem.h"

#ifndef __SYSTEMARDUINOIMPL
#define __SYSTEMARDUINOIMPL

class SystemArduinoImpl : public ISystem
{
public:
    virtual ~SystemArduinoImpl() {}

    virtual void sleep( uint32_t val )
    {
        delay( val );
    }
};

#endif

