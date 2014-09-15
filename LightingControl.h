#include "ILighting.h"
#include "ISystem.h"

#ifndef _IRISLIGHTINGCONTROL_h
#define _IRISLIGHTINGCONTROL_h

class LightingControl
{
public:
    LightingControl( ILighting* lighting,
                     ISystem* system );
    void init();

private:
    ILighting* m_pLights;
    ISystem* m_pSystem;
};

#endif

