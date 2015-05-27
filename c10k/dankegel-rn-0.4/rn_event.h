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

#ifndef rn_event_H
#define rn_event_H
#include <errno.h>
#include <time.h>   
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rn_pollevent_s;

typedef int (*rn_callback_fn_t)(struct rn_pollevent_s *event);

struct rn_client_s {
	/* The callback fn */
	rn_callback_fn_t pfn;

	/* The data to be passed back */
	void *data;
}; 

typedef struct rn_client_s rn_client_t;

struct rn_pollevent_s {
	/* the file descriptor that is ready for I/O (same as in struct pollfd). */
	int fd;

	/* the kind of I/O this fd is currently ready for (same as in struct pollfd). */
	short revents;

	/* the object to call to handle I/O on this fd. */
	rn_client_t client;
};

typedef struct rn_pollevent_s rn_pollevent_t;

#ifdef __cplusplus
}
#endif

#endif
