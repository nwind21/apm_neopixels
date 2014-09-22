#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include "LightingControl.h"
#include "LightingIrisImpl.h"
#include "SystemArduinoImpl.h"
#include "Timer.h"

LightingIrisImpl lights;
SystemArduinoImpl system;

void setup()
{
    Serial.begin( 115200 );
    LightingControl::initialize( &lights,
                                 &GLOBAL_TIMER );
    LightingControl::queueLightSequence( LightingControl::LightSequence_SystemCheck );
}

void loop()
{
    GLOBAL_TIMER.update();
}

