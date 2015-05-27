/*--------------------------------------------------------------------------
 Copyright 1999,2001, Dan Kegel http://www.kegel.com/
 Copyright 2003 Ixia http://www.ixiacom.com/
 See the file COPYING

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
 Portable clock functions.
--------------------------------------------------------------------------*/
#ifndef rn_eclock_h
#define rn_eclock_h

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/* FIXME: prefix identifiers declared by this file with rn_ */

/*--------------------------------------------------------------------------
 Get current time, in clock ticks.
 Return type is int.
--------------------------------------------------------------------------*/
#define eclock_HERTZ 1000
#define eclock_TICKSPERUSEC 1000

extern struct timeval eclock_timeval;
#define eclock() (gettimeofday(&eclock_timeval, NULL), \
	((int)((eclock_timeval.tv_sec * eclock_HERTZ) + (eclock_timeval.tv_usec / eclock_TICKSPERUSEC))))

/*--------------------------------------------------------------------------
 Get number of clock ticks per second, in hertz.  This evaluates to a 
 system call, so call it just once at the start of the program.
 Return type is int.
--------------------------------------------------------------------------*/
#define eclock_hertz() eclock_HERTZ

/*--------------------------------------------------------------------------
 Safe way to compare to eclock() values to see which is after the other.
 Assumes the largest interval to be compared is one half the maximum
 representable in a long.

 Returns true if time a is after time b.
--------------------------------------------------------------------------*/
#define eclock_after(a, b) (((long)((a)-(b))) > 0)
/*inline bool eclock_after(clock_t a, clock_t b)
{
	long diff = (long) (a - b);
	//DPRINT(("eclock_after(%d, %d): diff %d\n", a, b, diff));
	return (diff > 0);
}*/

/*--------------------------------------------------------------------------
 Safe way to compare to eclock() values to see which is after the other.
 Assumes the largest interval to be compared is one half the maximum
 representable in a long.

 Returns true if time a is before time b.
--------------------------------------------------------------------------*/
#define eclock_before(a, b) (((long)((a)-(b))) < 0)
/*inline bool eclock_before(clock_t a, clock_t b)
{
	long diff = (long) (a - b);
	//DPRINT(("eclock_before(%d, %d): diff %d\n", a, b, diff));
	return (diff < 0);
}
*/

#endif
