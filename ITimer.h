/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by Simon Monk
 http://www.simonmonk.org
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ITimer_h
#define ITimer_h

#include <inttypes.h>

class ITimer
{
public:
  virtual ~ITimer( void ) {}

  virtual int8_t every( unsigned long period, void( *callback )(void) ) = 0;
  virtual int8_t every( unsigned long period, void( *callback )(void), int repeatCount ) = 0;
  virtual int8_t after( unsigned long duration, void( *callback )(void) ) = 0;
  
  virtual void stop( int8_t id ) = 0;
  virtual void update( void ) = 0;
  virtual void update( unsigned long now ) = 0;

};

#endif
