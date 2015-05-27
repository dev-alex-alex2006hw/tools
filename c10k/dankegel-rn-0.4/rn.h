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

#ifndef rn_h
#define rn_h

#ifdef __cplusplus
extern "C" {
#endif

#include <rn_event.h>
#include <rn_sigio.h>
#include <rn_dev_epoll.h>
#include <rn_sys_epoll.h>

/* If you really need to, you can tell which of these is
 * active by comparing one of the function pointers against
 * the four real functions it might have been set to.
 */
typedef union {
#ifdef HAVE_F_SETSIG
	struct rn_sigio sigio;
#endif
#ifdef HAVE_LINUX_EVENTPOLL_H_EP_ALLOC
	struct rn_dev_epoll epoll;
#endif
#if defined(HAVE_SYS_EPOLL_H) && defined(HAVE_EPOLL_CREATE)
	struct rn_sys_epoll sys_epoll;
#endif
} rn_t;

#define rn_POLLIN  POLLIN
#define rn_POLLOUT POLLOUT
#define rn_POLLERR POLLERR
#define rn_POLLHUP POLLHUP

/* The function pointers apps use to access the rn_t methods.
 * I used to use #define's to do this indirection without runtime penalty,
 * but it turns out to be impossible to tell at compile time which of
 * the schemes is best to use, so I now pick one at runtime.
 */

/** Tell the rn_t which signal number to use.  Call once after init(), before add(). */
extern int (*rn_setSignum)(rn_t *, int signum);

/** Initialize the rn_t. */
extern int (*rn_init)(rn_t *, int maxfds);

/** Release any resouces allocated internally by this rn_t. */
extern void (*rn_shutdown)(rn_t *);

/**
 Sets the flags of fd for use with sigio
 On exit, the fd is ready for use with rn_add
 Note: Overrides the old flags of fd.
 @param fd - the file descriptor to be used for IO
 @param pid - the pid of the process. 
 @return 0 on success, errno on failure
*/
extern int (*rn_prepare_fd_for_add)(int fd, int pid);

/**
 Add a file descriptor to the set we monitor. 
 Caller should already have established a handler for SIGIO.
 @param fd file descriptor to add
 @param pfn function to call when fd is ready
 @param data context pointer to pass to pfn
 */
extern int (*rn_add)(rn_t *, int fd, rn_callback_fn_t pfn, void *data);

/** Remove a file descriptor. */
extern int (*rn_del)(rn_t *, int fd);

/**
 Sleep at most timeout_millisec waiting for an I/O readiness event
 on the file descriptors we're watching, and dispatch events to
 the handler for each file descriptor that is ready for I/O.
 This is included as an example of how to use
 waitForEvents and getNextEvent.  Real programs should probably
 avoid waitAndDispatchEvents and call waitForEvents and getNextEvent
 instead for maximum control over client deletion.
 */
extern int (*rn_waitAndDispatchEvents)(rn_t *, int timeout_millisec);


/*----- Users should not need to worry about the following five functions normally. -----*/

/* Set up pointers for sys_epoll */
int rn_config_sys_epoll();

/* Set up pointers for /dev/epoll */
int rn_config_dev_epoll();

/* Set up pointers for sigio */
int rn_config_sigio();

/* Set up pointers for "sorry, not implemented" */
int rn_config_not_implemented();

/* Pick the default type of rn_t, and set function pointers. 
 * This is run when the program or shared library is loaded!
 */

void __attribute__ ((constructor)) rn_config_default();

/*----- Users should not need to worry about the previous five functions normally. -----*/

#ifdef __cplusplus
}
#endif

#endif
