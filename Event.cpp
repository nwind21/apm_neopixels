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

// For Arduino 1.0 and earlier
#if defined _WIN32
#include <Windows.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Event.h"

#if defined _WIN32
uint32_t millis()
{
    SYSTEMTIME time;
    GetSystemTime( &time );
    WORD millis = (time.wSecond * 1000) + time.wMilliseconds;
    return millis;
}
#endif

Event::Event(void)
{
	eventType = EVENT_NONE;
}

void Event::update(void)
{
    unsigned long now = millis();
    update(now);
}

void Event::update(unsigned long now)
{
	if (now - lastEventTime >= period)
	{
        (*callback)();
		lastEventTime = now;
		count++;
	}
	if (repeatCount > -1 && count >= repeatCount)
	{
		eventType = EVENT_NONE;
	}
}
