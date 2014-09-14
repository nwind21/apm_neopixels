#include "nw21_types.h"

#ifndef __II2C
#define __II2C

class II2C
{
public:
    enum II2C_ERROR
    {
        II2C_ERROR_NONE,
        II2C_ERROR_NORESPONSE,
        II2C_ERROR_NOTENOUGHDATA,
    };

    virtual ~II2C() {}

    virtual II2C_ERROR open( uint8_t address ) = 0;
    virtual II2C_ERROR send( uint8_t* data,
                             uint16_t dataLength ) = 0;
    virtual II2C_ERROR recv( uint8_t* data,
                             uint16_t& dataLength ) = 0;
    virtual void close( ) = 0;
};

#endif

