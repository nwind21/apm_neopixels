// 
// 
// 

#include "LightingControl.h"

LightingControl::LightingControl( ILighting* lighting,
                                  ISystem* system )
{
    m_pLights = lighting;
    m_pSystem = system;
}

void LightingControl::init()
{

    // Test sequence
    m_pLights->initialize();

    m_pLights->strobe( 3 );
    m_pLights->off();

    uint8_t iPixel = 0;
    uint8_t iArms = 0;
    uint32_t checkColor[] =
    {
        COLOR_RGB( 255, 0, 0 )
    };

    int8_t incrementer = 1;
    uint8_t lastPixel = 0;
    uint8_t currentPixel = 0;
    uint8_t cnt = 0;
    uint8_t maxPixelIndex = m_pLights->length( ILighting::ARM_1 ) - 1;
    uint8_t armCnt = m_pLights->cnt();

    while ( cnt < (sizeof( checkColor ) / sizeof( uint32_t )) )
    {
        if ( currentPixel == 0 )
        {
            incrementer = 1;
            for ( iArms = 0; iArms < armCnt; iArms++ )
            {
                m_pLights->setColor( static_cast<ILighting::ARM>(iArms),
                                     checkColor[cnt] );
            }
        }

        for ( iArms = 0; iArms < armCnt; iArms++ )
        {
            m_pLights->off( static_cast<ILighting::ARM>(iArms),
                            lastPixel );
            m_pLights->on( static_cast<ILighting::ARM>(iArms),
                           currentPixel );
        }
        lastPixel = currentPixel;
        if ( currentPixel == maxPixelIndex )
        {
            incrementer = -1;
        }

        currentPixel += incrementer;

        if ( currentPixel == 0 )
        {
            cnt++;
        }
        m_pSystem->sleep( 75 );
    }

    m_pLights->off();
}


