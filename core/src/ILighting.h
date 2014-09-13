#ifndef __ILIGHTING
#define __ILIGHTING

#include "nw21_types.h"

#define COLOR_RGB( r, g, b )  ( ( r & 0xFF ) << 16 | ( g & 0xFF ) << 8 | ( b & 0xFF ) )

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
        ARM_1,
        ARM_2,
        ARM_3,
        ARM_4
    };

    virtual ~ILighting() {};

    // Turn off all LEDS.
    virtual void off( ) = 0;

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

    // Turn on the arm, if setColor was not called the color may be
    // undefined.
    virtual void on( ILighting::ARM arm ) = 0;

    // All LEDS on then off in a rapid flash
    virtual void strobe( ILighting::ARM arm ) = 0;
};

#endif

