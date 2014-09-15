#include "nw21_types.h"

#ifndef __ILIGHTING
#define __ILIGHTING

#define COLOR_RGB( r, g, b )  ( ( (uint32_t)r & 0xFF ) << 16 | ( (uint32_t)g & 0xFF ) << 8 | ( (uint32_t)b & 0xFF ) )
#define R_COLOR( rgb )  ( ( rgb >> 16 ) & 0xFF )
#define G_COLOR( rgb )  ( ( rgb >> 8 ) & 0xFF )
#define B_COLOR( rgb )  ( rgb & 0xFF )

class ILighting
{
public:
    /* Arms are designed starting from the first arm from the front 180deg going clockwise.
       E.g.      For a X        For a Y
                  Front          
                 1     2        1     2

                 4     3           3
    */
    enum ARM
    {
        ARM_1 = 0,
        ARM_2 = 1,
        ARM_3 = 2,
        ARM_4 = 3
    };

    virtual ~ILighting() {};

    virtual void initialize() = 0;

    // Return the number of arms
    virtual uint8_t cnt( ) = 0;

    // Return the number of lights on the ARM
    virtual uint8_t length( ILighting::ARM arm ) = 0;

    // Set the RGB color on the LED @ position X.
    // 0 is always the LED closest to the body.
    //
    // If the LED index doeen't exist, ignore the command.
    // If RGB is not supported, ignore the command.
    virtual void setColor( ILighting::ARM arm,
                           uint8_t index,
                           uint32_t color ) = 0;
    virtual void setColor( ILighting::ARM arm,
                           uint32_t color ) = 0;
    virtual void setColorAndDisplay( ILighting::ARM arm,
                                     uint8_t index,
                                     uint32_t color ) = 0;
    virtual void setColorAndDisplay( ILighting::ARM arm,
                                     uint32_t color ) = 0;

    // Turn on the arm, if setColor was not called the color may be
    // undefined.
    virtual void on( ) = 0;

    virtual void on( ILighting::ARM arm ) = 0;

    virtual void on( ILighting::ARM arm,
                     uint8_t index ) = 0;

    // Turn off all LEDS.
    virtual void off() = 0;

    // Turn off the arm
    virtual void off( ILighting::ARM arm ) = 0;

    // Turn off pixel
    virtual void off( ILighting::ARM arm,
                      uint8_t index ) = 0;

    // All LEDS on then off in a rapid flash
    virtual void strobe( uint8_t times ) = 0;
};

#endif

