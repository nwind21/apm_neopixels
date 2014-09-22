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

#ifndef ITimerMock_h
#define ITimerMock_h

#include <inttypes.h>
#include "gmock/gmock.h"
#include "Timer.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class ITimerMock : public ITimer
{
public:
    virtual ~ITimerMock( void ) {}

    void setReal( ITimer* real )
    {
        m_pReal = real;
        // By default, all calls are delegated to the real object.
        ON_CALL( *this, every( _, _ ) )
            .WillByDefault( Invoke( m_pReal, static_cast<int8_t( ITimer::* )(unsigned long, void( *)(void))>(&ITimer::every) ) );
        ON_CALL( *this, every( _, _, _ ) )
            .WillByDefault( Invoke( m_pReal, static_cast<int8_t( ITimer::* )(unsigned long, void( *)(void), int)>(&ITimer::every) ) );

        ON_CALL( *this, after( _, _ ) )
            .WillByDefault( Invoke( m_pReal, &ITimer::after ) );

        ON_CALL( *this, stop( _ ) )
            .WillByDefault( Invoke( m_pReal, &ITimer::stop ) );

        ON_CALL( *this, update( ) )
            .WillByDefault( Invoke( m_pReal, static_cast<void(ITimer::*)(void)>(&ITimer::update) ) );
        ON_CALL( *this, update( _ ) )
            .WillByDefault( Invoke( m_pReal, static_cast<void(ITimer::*)(unsigned long)>(&ITimer::update) ) );
    }

    MOCK_METHOD2( every, int8_t( unsigned long period, void( *callback )(void) ) );
    MOCK_METHOD3( every, int8_t( unsigned long period, void( *callback )(void), int repeatCount ) );
    MOCK_METHOD2( after, int8_t( unsigned long duration, void( *callback )(void) ) );
  
    MOCK_METHOD1( stop, void( int8_t id ) );
    MOCK_METHOD0( update, void( void ) );
    MOCK_METHOD1( update, void( unsigned long now ) );

private:
    ITimer* m_pReal;

};

#endif
