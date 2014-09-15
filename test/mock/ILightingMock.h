#include "ILighting.h"

class ILightingMock : public ILighting
{
public:
    virtual ~ILightingMock( ) {}

    MOCK_METHOD0( initialize, void() );

    MOCK_METHOD0( on, void() );
    MOCK_METHOD1( on, void( ILighting::ARM arm ) );
    MOCK_METHOD2( on, void( ILighting::ARM arm,
                            uint8_t index ) );
    MOCK_METHOD0( off, void( ) );
    MOCK_METHOD1( off, void( ILighting::ARM arm ) );
    MOCK_METHOD2( off, void( ILighting::ARM arm,
                             uint8_t index ) );
    MOCK_METHOD0( cnt, uint8_t( ) );
    MOCK_METHOD1( length, uint8_t( ILighting::ARM arm ) );
    MOCK_METHOD3( setColor, void( ILighting::ARM arm,
                                  uint8_t index,
                                  uint32_t color ) );
    MOCK_METHOD2( setColor, void( ILighting::ARM arm,
                                  uint32_t color ) );
    MOCK_METHOD3( setColorAndDisplay, void ( ILighting::ARM arm,
                                             uint8_t index,
                                             uint32_t color ) );
    MOCK_METHOD2( setColorAndDisplay, void( ILighting::ARM arm,
                                            uint32_t color ) );
    MOCK_METHOD1( strobe, void( uint8_t times ) );

};