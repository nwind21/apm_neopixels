/*
 * I2CImpl.cpp
 *
 * Created: 9/13/2014 7:16:51 PM
 *  Author: fchan
 */ 

#include "II2C.h"

#ifndef __I2CARDUINOIMPL_H
#define __I2CARDUINOIMPL_H

class I2CArduinoImpl : public II2C
{
public:
	virtual II2C_ERROR open( uint8_t address );
	virtual II2C_ERROR send( uint8_t* data,
							 uint16_t dataLength );
	virtual II2C_ERROR recv( uint8_t* data,
	                         uint16_t& dataLength );
	virtual void close( );
	
};

#endif
