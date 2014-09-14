/*
 * I2CImpl.cpp
 *
 * Created: 9/13/2014 7:16:51 PM
 *  Author: fchan
 */ 

#include "I2CArduinoImpl.h"

I2CArduinoImpl::II2C_ERROR I2CArduinoImpl::open( uint8_t address )
{
    return II2C_ERROR_NONE;
}

I2CArduinoImpl::II2C_ERROR I2CArduinoImpl::send( uint8_t* data,
                                                 uint16_t dataLength )
{
    return II2C_ERROR_NONE;							 
}

I2CArduinoImpl::II2C_ERROR I2CArduinoImpl::recv( uint8_t* data,
	                                             uint16_t& dataLength )
{
    return II2C_ERROR_NONE;
}

void I2CArduinoImpl::close( )
{
}

