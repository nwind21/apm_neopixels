// 
// 
// 

#include "LightingControl.h"

void LightingControl::init()
{

    // Test sequence
    lights.initialize();

    lights.strobe( 3 );
    lights.off();

    uint8_t iPixel = 0;
    uint8_t iArms = 0;
    uint32_t checkColor[] =
    {
        COLOR_RGB( 255, 0, 0 ),
        COLOR_RGB( 255, 255, 0 ),
        COLOR_RGB( 0, 255, 0 ),
        COLOR_RGB( 0, 255, 255 ),
        COLOR_RGB( 0, 0, 255 ),
    };

    for ( iArms = 0; iArms < lights.cnt(); iArms++ )
    {
        lights.setColor( static_cast<ILighting::ARM>(iArms),
            COLOR_RGB( 255, 255, 255 ) );
    }
    lights.off();

    int8_t incrementer = 1;
    uint8_t lastPixel = 0;
    uint8_t currentPixel = 0;
    uint8_t cnt = 0;
    uint8_t maxPixelIndex = lights.length( ILighting::ARM_1 ) - 1;
    while ( cnt < (sizeof( checkColor ) / sizeof( uint32_t )) )
    {
        if ( currentPixel == 0 )
        {
            incrementer = 1;
            cnt++;
            for ( iArms = 0; iArms < lights.cnt(); iArms++ )
            {
                lights.setColor( static_cast<ILighting::ARM>(iArms),
                    checkColor[cnt] );
            }
        }
        for ( iArms = 0; iArms < lights.cnt(); iArms++ )
        {
            lights.off( static_cast<ILighting::ARM>(iArms),
                lastPixel );
            lights.on( static_cast<ILighting::ARM>(iArms),
                currentPixel );
        }
        lastPixel = currentPixel;
        if ( currentPixel == maxPixelIndex )
        {
            incrementer = -1;
        }

        currentPixel += incrementer;
        Serial.println( currentPixel );
        delay( 50 );
    }
    lights.off();
}


