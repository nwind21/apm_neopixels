#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "II2CMock.h"
#include "ILightingMock.h"

TEST( ILighting_RGBMacros, RGBU32_Positive )
{
    uint32_t value = COLOR_RGB( 1, 2, 3 );
    ASSERT_TRUE( value == 0x00010203 );
}

TEST( ILighting_RGBMacros, RColor_Positive )
{
    uint32_t value = COLOR_RGB( 255, 1, 2 );
    ASSERT_TRUE( R_COLOR( value ) == 255 );
    ASSERT_TRUE( G_COLOR( value ) == 1 );
    ASSERT_TRUE( B_COLOR( value ) == 2 );
}

TEST( ILighting_RGBMacros, GColor_Positive )
{
    uint32_t value = COLOR_RGB( 1, 255, 2 );
    ASSERT_TRUE( R_COLOR( value ) == 1 );
    ASSERT_TRUE( G_COLOR( value ) == 255 );
    ASSERT_TRUE( B_COLOR( value ) == 2 );
}

TEST( ILighting_RGBMacros, BColor_Positive )
{
    uint32_t value = COLOR_RGB( 1, 2, 255 );
    ASSERT_TRUE( R_COLOR( value ) == 1 );
    ASSERT_TRUE( G_COLOR( value ) == 2 );
    ASSERT_TRUE( B_COLOR( value ) == 255 );
}