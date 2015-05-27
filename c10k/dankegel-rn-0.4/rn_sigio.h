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

#ifndef rn_sigio_H
#define rn_sigio_H

#include <rn_config.h>	/* must come first */

#ifdef HAVE_F_SETSIG

#include <assert.h>
#include <errno.h>
#include <poll.h>
#include <sys/types.h>
#include <time.h>   
#include <unistd.h>
#include <rn_event.h>

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * A class to monitor a set of file descriptors for readiness events.
 * This implementation is a wrapper around the F_SETSIG event delivery 
 * scheme provided by Linux.
 *
 * Warning: the 2.4 linux kernel works fine with all parts of
 * this class except wakeUp().  The 2.4 linux kernel does not by default 
 * support using SIGIO with pipes.  See Jeremy Elson's patch,
 * http://www.cs.helsinki.fi/linux/linux-kernel/2002-13/0191.html
 * if you want to use this class with pipes, or if you want to use
 * the wakeUp method of this class.
 */

struct rn_sigio {
	/** Which realtime signal number to use for I/O readiness notification. */
	int m_signum;

	/** Set including just the above signal */
	sigset_t m_sigset;

	/** Each fd we watch has an entry in this array. */
	rn_client_t *m_fds;

	/** Number of elements worth of heap allocated for m_fds. */
	int m_fds_alloc;

	/** How many fds we are watching. */
	int m_fds_used;
};

/** Tell the rn_t which signal number to use.  Call once after init(), before add(). */
int rn_sigio_setSignum(struct rn_sigio *, int signum);

/** Initialize the rn_t. */
int rn_sigio_init(struct rn_sigio *, int maxfds);

/** Release any resouces allocated internally by this rn_t. */
void rn_sigio_shutdown(struct rn_sigio *);

/**
 Sets the flags of fd for use with sigio
 On exit, the fd is ready for use with rn_sigio_add
 Note: Overrides the old flags of fd.
 @param fd - the file descriptor to be used for IO
 @param pid - the pid of the process. 
*/
int rn_sigio_prepare_fd_for_add(int fd, int pid);

/**
 Add a file descriptor to the set we monitor. 
 Caller should already have established a handler for SIGIO.
 @param fd file descriptor to add
 @param pfn function to call when fd is ready
 @param data context pointer to pass to pfn
 */
int rn_sigio_add(struct rn_sigio *, int fd, rn_callback_fn_t pfn, void *data);

/** Remove a file descriptor. */
int rn_sigio_del(struct rn_sigio *, int fd);

/**
 Sleep at most timeout_millisec waiting for an I/O readiness event
 on the file descriptors we're watching, and dispatch events to
 the handler for each file descriptor that is ready for I/O.
 This is included as an example of how to use
 waitForEvents and getNextEvent.  Real programs should probably
 avoid waitAndDispatchEvents and call waitForEvents and getNextEvent
 instead for maximum control over client deletion.
 */
int rn_sigio_waitAndDispatchEvents(struct rn_sigio *, int timeout_millisec);

#ifdef __cplusplus
}
#endif

#endif
#endif
