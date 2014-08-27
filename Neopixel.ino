#include "Adafruit_NeoPixel.h"

#define FL_PIN 6
#define FR_PIN 5
#define BL_PIN 4
#define BR_PIN 3

enum LIGHTING
{
    LIGHTING_FRONT_LEFT = 0,
    LIGHTING_FRONT_RIGHT,
    LIGHTING_BACK_LEFT,
    LIGHTING_BACK_RIGHT,
    LIGHTING_END
};

enum LIGHT_INDEX
{
};

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel lights[4] = { Adafruit_NeoPixel(5, FL_PIN, NEO_GRB + NEO_KHZ800),
                                Adafruit_NeoPixel(5, FR_PIN, NEO_GRB + NEO_KHZ800),
                                Adafruit_NeoPixel(5, BL_PIN, NEO_GRB + NEO_KHZ800),
                                Adafruit_NeoPixel(5, BR_PIN, NEO_GRB + NEO_KHZ800) };


void pulseNavigationLights( )
{
    static bool on = false;
    if ( !on )
    {
        lights[LIGHTING_FRONT_LEFT].setPixelColor( 4,
                                                   86,
                                                   8,
                                                   19 );
        lights[LIGHTING_FRONT_RIGHT].setPixelColor( 4,
                                                    0,
                                                    255,
                                                    0 );
    }
    else
    {
        lights[LIGHTING_FRONT_LEFT].setPixelColor( 4,
                                                   0 );
        lights[LIGHTING_FRONT_RIGHT].setPixelColor( 4,
                                                    0 );
    }
    lights[LIGHTING_FRONT_LEFT].show();
    lights[LIGHTING_FRONT_RIGHT].show();
    on = !on;

}


enum LIGHT_STATE
{
    LIGHT_STATE_BLINK,
    LIGHT_STATE_OFF,
};

void setup()
{
    for ( unsigned char i = 0; i < LIGHTING_END; i++ )
    {
        lights[i].begin();
        lights[i].show();
    }
    lights[LIGHTING_FRONT_LEFT].setStripColor( 0, 255, 0 );
    lights[LIGHTING_FRONT_RIGHT].setStripColor( 255, 0, 0 );

    // Display the pattern
    for ( unsigned char i = 0; i < LIGHTING_END; i++ )
    {
        lights[i].show();
    }
}

void loop()
{
    static unsigned char brightness = 1;
    static char incrementer = 1;

    // Display the pattern
    for ( unsigned char i = 0; i < LIGHTING_END; i++ )
    {    
        lights[i].setBrightness( brightness );
        lights[i].show();
    }
   
    if ( brightness == 100 )
        incrementer = -1;
    if ( brightness == 1 )
        incrementer = 1;
            
    brightness += incrementer;
    delay(100);
}
