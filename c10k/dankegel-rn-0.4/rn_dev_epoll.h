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

#ifndef rn_dev_epoll_H
#define rn_dev_epoll_H

#include <rn_config.h>	/* must come first */

#ifdef HAVE_LINUX_EVENTPOLL_H_EP_ALLOC
#include <assert.h>
#include <errno.h>
#include <linux/eventpoll.h>
#include <linux/poll.h>
#include <sys/types.h>
#include <time.h>   
#include <unistd.h>
#include <rn_event.h>

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * A class to monitor a set of file descriptors for readiness events.
 * This implementation is a wrapper around the /dev/epoll event delivery 
 * scheme provided by Davide Libenzi's patch
 * (see http://www.xmailserver.org/linux-patches/nio-improve.html )
 */

struct rn_dev_epoll {
	/* max number of fds epoll was told to happen at open time */
	int maxfds;

	/* The fd to /dev/epoll */
	int epfd;

	/* The memory-mapped buffer to that fd */
	char *epmap;

	/* Each fd we watch has an entry in this array. */
	rn_client_t *m_fds;

	/* Number of elements worth of heap allocated for m_fds. */
	int m_fds_alloc;

	/* How many fds we are watching. */
	int m_fds_used;
};

/* Initialize the rn_t. */
int rn_dev_epoll_init(struct rn_dev_epoll *, int maxfds);

/* Release any resouces allocated internally by this rn_t. */
void rn_dev_epoll_shutdown(struct rn_dev_epoll *);

/**
 Sets the flags of fd for use with epoll
 On exit, the fd is ready for use with rn_dev_epoll_add
 Note: Overrides the old flags of fd.
 @param fd - the file descriptor to be used for IO
 @param pid - the pid of the process. Ignored for epoll
*/
int rn_dev_epoll_prepare_fd_for_add(int fd, int pid);

/**
 Add a file descriptor to the set we monitor. 
 Caller should already have established a handler for SIGIO.
 @param fd file descriptor to add
 @param pfn function to call when fd is ready
 @param data context pointer to pass to pfn
 */
int rn_dev_epoll_add(struct rn_dev_epoll *, int fd, rn_callback_fn_t pfn, void *data);

/* Remove a file descriptor. */
int rn_dev_epoll_del(struct rn_dev_epoll *, int fd);

/**
 Sleep at most timeout_millisec waiting for an I/O readiness event
 on the file descriptors we're watching, and dispatch events to
 the handler for each file descriptor that is ready for I/O.
 This is included as an example of how to use
 waitForEvents and getNextEvent.  Real programs should probably
 avoid waitAndDispatchEvents and call waitForEvents and getNextEvent
 instead for maximum control over client deletion.
 */
int rn_dev_epoll_waitAndDispatchEvents(struct rn_dev_epoll *, int timeout_millisec);

#ifdef __cplusplus
}
#endif

#endif
#endif
