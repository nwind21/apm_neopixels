/*
 * LightingIrisImpl.cpp
 *
 * Created: 9/13/2014 7:34:28 PM
 *  Author: fchan
 */ 

#include "ILighting.h"
#include "Adafruit_NeoPixel.h"

#ifndef __LIGHTINGIRISIMPL_H
#define __LIGHTINGIRISIMPL_H

#define NUM_PIXELS      (5)
#define NUM_ARMS        (4)
class LightingIrisImpl : public ILighting
{
public:
    LightingIrisImpl();
    virtual ~LightingIrisImpl() {}
    virtual void off( );

    virtual void initialize();
    virtual uint8_t length( ILighting::ARM arm );
    virtual uint8_t cnt( );
    virtual void setColor( ILighting::ARM arm,
                           uint8_t index,
                           uint32_t color );
    virtual void setColor( ILighting::ARM arm,
                           uint32_t color );
    virtual void setColorAndDisplay( ILighting::ARM arm,
                                     uint8_t index,
                                     uint32_t color );
    virtual void setColorAndDisplay( ILighting::ARM arm,
                                     uint32_t color );

    virtual void on( );
    virtual void on( ILighting::ARM arm );
    virtual void on( ILighting::ARM arm,
                     uint8_t index );
    virtual void off( ILighting::ARM arm );
    virtual void off( ILighting::ARM arm,
                      uint8_t index );
    virtual void strobe( uint8_t times );
    virtual uint32_t rgb( uint8_t r, uint8_t g, uint8_t b )
    {
        uint32_t color = r;
        color <<= 8;
        color |= g;
        color <<= 8;
        color |= b;
        return color ;
    }

private:
    void showAll();
    void brightness( uint8_t val );

private:
    static Adafruit_NeoPixel m_sLight[NUM_ARMS];
    static uint32_t m_sCurrentColor[NUM_ARMS][NUM_PIXELS];
    static bool m_sInitialized;
};

#endif

