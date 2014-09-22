/*
 * LightingIrisImpl.cpp
 *
 * Created: 9/13/2014 7:34:28 PM
 *  Author: fchan
 */ 
#include "LightingIrisImpl.h"

#define ARM0_PIN 6
#define ARM1_PIN 5
#define ARM2_PIN 4
#define ARM3_PIN 3

bool LightingIrisImpl::m_sInitialized = false;

uint32_t LightingIrisImpl::m_sCurrentColor[4][NUM_PIXELS] =
{
    0
};

Adafruit_NeoPixel LightingIrisImpl::m_sLight[4] =
{
    Adafruit_NeoPixel( NUM_PIXELS, ARM0_PIN, NEO_GRB + NEO_KHZ800 ),
    Adafruit_NeoPixel( NUM_PIXELS, ARM1_PIN, NEO_GRB + NEO_KHZ800 ),
    Adafruit_NeoPixel( NUM_PIXELS, ARM3_PIN, NEO_GRB + NEO_KHZ800 ),
    Adafruit_NeoPixel( NUM_PIXELS, ARM2_PIN, NEO_GRB + NEO_KHZ800 )
};


LightingIrisImpl::LightingIrisImpl()
{

}

void LightingIrisImpl::initialize( )
{
    for ( int iLights = 0; iLights < sizeof( m_sLight ) / sizeof( Adafruit_NeoPixel ); iLights++ )
    {
        m_sLight[iLights].begin();
    }
    showAll();
    m_sInitialized = true;

    // small sleep to get things setttled down
    brightness( 150 );
}

void LightingIrisImpl::on( )
{
    on( ILighting::ARM_1 );
    on( ILighting::ARM_2 );
    on( ILighting::ARM_3 );
    on( ILighting::ARM_4 );
    showAll();
}

void LightingIrisImpl::on( ILighting::ARM arm )
{
    for ( uint8_t iPixel = 0; iPixel < length( arm ); iPixel++ )
    {
        setColor( arm,
                  iPixel,
                  m_sCurrentColor[arm][iPixel] );
    }
    m_sLight[arm].show();
}

void LightingIrisImpl::on( ILighting::ARM arm,
                           uint8_t index )
{
    setColor( arm,
              index,
              m_sCurrentColor[arm][index] );
    m_sLight[arm].show();
}


void LightingIrisImpl::off( )
{
    off( ILighting::ARM_1 );
    off( ILighting::ARM_2 );
    off( ILighting::ARM_3 );
    off( ILighting::ARM_4 );
}

void LightingIrisImpl::off( ILighting::ARM arm )
{
    m_sLight[arm].setStripColor( 0, 0, 0 );
    m_sLight[arm].show();
}

void LightingIrisImpl::off( ILighting::ARM arm,
                            uint8_t index )
{
    m_sLight[arm].setPixelColor( index,
                                 0 );
    m_sLight[arm].show();
}


void LightingIrisImpl::showAll( )
{
    for ( int iLights = 0; iLights < sizeof( m_sLight ) / sizeof( Adafruit_NeoPixel ); iLights++ )
    {
        m_sLight[iLights].show();
    }
}

void LightingIrisImpl::brightness( uint8_t val )
{
    for ( uint8_t iLights = 0; iLights < sizeof( m_sLight ) / sizeof( Adafruit_NeoPixel ); iLights++ )
    {
        m_sLight[iLights].setBrightness( val );
    }
}

uint8_t LightingIrisImpl::cnt()
{
    return NUM_ARMS;
}

// Return the number of lights on the ARM
uint8_t LightingIrisImpl::length( ILighting::ARM arm )
{
    (void)arm;
    return NUM_PIXELS;
}

void LightingIrisImpl::setColor( ILighting::ARM arm,
                                 uint8_t index,
                                 uint32_t color )
{
    m_sLight[arm].setPixelColor( index,
                                 color );
    m_sCurrentColor[arm][index] = color;
}

void LightingIrisImpl::setColor( ILighting::ARM arm,
                                 uint32_t color )
{
    for ( uint8_t iPixel = 0; iPixel < length( arm ); iPixel++ )
    {
        setColor( arm,
                  iPixel,
                  color );
    }
}

void LightingIrisImpl::setColorAndDisplay( ILighting::ARM arm,
                                           uint8_t index,
                                           uint32_t color )
{
    setColor( arm,
              index,
              color );
    m_sLight[arm].show();
}

void LightingIrisImpl::setColorAndDisplay( ILighting::ARM arm,
                                           uint32_t color )
{
    setColor( arm,
              color );
    m_sLight[arm].show();
}

void LightingIrisImpl::strobeOn( )
{
    for ( int  iLights = 0; iLights < sizeof( m_sLight ) / sizeof( Adafruit_NeoPixel ); iLights++ )
    {
        m_sLight[iLights].setBrightness( 255 );
        m_sLight[iLights].setStripColor( 255,
                                         255,
                                         255 );
    }
    showAll();
}

void LightingIrisImpl::strobeOff()
{
    brightness( 100 );
    for ( int iLights = 0; iLights < sizeof( m_sLight ) / sizeof( Adafruit_NeoPixel ); iLights++ )
    {
        m_sLight[iLights].setStripColor( 0,
                                         0,
                                         0 );
    }
    showAll();
}
