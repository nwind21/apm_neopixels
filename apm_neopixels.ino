#include "LightingControl.h"
#include "LightingIrisImpl.h"
#include "SystemArduinoImpl.h"

LightingIrisImpl lights;
SystemArduinoImpl system;
LightingControl lightControl( &lights,    
                              &system );

void setup()
{
    Serial.begin( 115200 );
    lightControl.init();
}

void loop()
{
}

