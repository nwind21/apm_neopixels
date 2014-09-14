#include "LightingControl.h"

LightingControl lightControl;

void setup()
{
    Serial.begin( 115200 );
    lightControl.init();
}

void loop()
{
}

