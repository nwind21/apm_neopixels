#include "II2C.h"

class II2CMock : public II2C
{
public:
    virtual ~II2CMock() {}

    MOCK_METHOD1( open, II2C_ERROR( uint8_t address ) );
    MOCK_METHOD2( send, II2C_ERROR( uint8_t* data,
                                    uint16_t dataLength ) );
    MOCK_METHOD2( recv, II2C_ERROR( uint8_t* data,
                                    uint16_t& dataLength ) );
    MOCK_METHOD0( close, void() );
};