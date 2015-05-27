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

/* see comments in rn.h for each global function and variable */

#include <errno.h>
#include <unistd.h>
#include "rn.h"

typedef int (*rn_setSignum_t)(rn_t *, int signum);
int (*rn_setSignum)(rn_t *, int signum);

typedef int (*rn_init_t)(rn_t *, int maxfds);
int (*rn_init)(rn_t *, int maxfds);

typedef void (*rn_shutdown_t)(rn_t *);
void (*rn_shutdown)(rn_t *);

typedef int (*rn_prepare_fd_for_add_t)(int fd, int pid);
int (*rn_prepare_fd_for_add)(int fd, int pid);

typedef int (*rn_add_t)(rn_t *, int fd, rn_callback_fn_t pfn, void *data);
int (*rn_add)(rn_t *, int fd, rn_callback_fn_t pfn, void *data);

typedef int (*rn_del_t)(rn_t *, int fd);
int (*rn_del)(rn_t *, int fd);

typedef int (*rn_waitAndDispatchEvents_t)(rn_t *, int timeout_millisec);
int (*rn_waitAndDispatchEvents)(rn_t *, int timeout_millisec);

int rn_config_sys_epoll()
{
	int status = ENOSYS;

#if defined(HAVE_SYS_EPOLL_H) && defined(HAVE_EPOLL_CREATE)
	int fd = epoll_create(100);
	if (fd != -1) {
		close(fd);
		
		rn_setSignum = (rn_setSignum_t)rn_sigio_setSignum;
		rn_init = (rn_init_t) rn_sigio_init;
		rn_shutdown = (rn_shutdown_t) rn_sigio_shutdown;
		rn_prepare_fd_for_add = (rn_prepare_fd_for_add_t) rn_sigio_prepare_fd_for_add;
		rn_add = (rn_add_t) rn_sigio_add;
		rn_del = (rn_del_t) rn_sigio_del;
		rn_waitAndDispatchEvents = (rn_waitAndDispatchEvents_t) rn_sigio_waitAndDispatchEvents;

		return 0;
	}
	status = errno;
#endif
	return status;
}


int rn_config_dev_epoll()
{
	int status = ENOSYS;

#ifdef HAVE_LINUX_EVENTPOLL_H_EP_ALLOC
	int fd = open("/dev/epoll", O_RDWR);
	if (fd != -1) {
		close(fd);

		rn_setSignum = (rn_setSignum_t)rn_dev_epoll_setSignum;
		rn_init = (rn_init_t) rn_dev_epoll_init;
		rn_shutdown = (rn_shutdown_t) rn_dev_epoll_shutdown;
		rn_prepare_fd_for_add = (rn_prepare_fd_for_add_t) rn_dev_epoll_prepare_fd_for_add;
		rn_add = (rn_add_t) rn_dev_epoll_add;
		rn_del = (rn_del_t) rn_dev_epoll_del;
		rn_waitAndDispatchEvents = (rn_waitAndDispatchEvents_t) rn_dev_epoll_waitAndDispatchEvents;

		return 0;
	}
	status = errno;
#endif
	return status;
}

int rn_config_sigio()
{
#ifdef HAVE_F_SETSIG
	/* Assume it's universally available.  It's been usable since 2.4.4 or so.  FIXME if anyone cares. */
	rn_setSignum = (rn_setSignum_t)rn_sigio_setSignum;
	rn_init = (rn_init_t) rn_sigio_init;
	rn_shutdown = (rn_shutdown_t) rn_sigio_shutdown;
	rn_prepare_fd_for_add = (rn_prepare_fd_for_add_t) rn_sigio_prepare_fd_for_add;
	rn_add = (rn_add_t) rn_sigio_add;
	rn_del = (rn_del_t) rn_sigio_del;
	rn_waitAndDispatchEvents = (rn_waitAndDispatchEvents_t) rn_sigio_waitAndDispatchEvents;
	return 0;
#else
	return ENOSYS;
#endif
}

/* placeholder function; called if no notification method rn knows how to use is working */
static int not_implemented_int()
{
	return ENOSYS;
}

/* placeholder function; called if no notification method rn knows how to use is working */
static void not_implemented_void()
{
	return;
}

int rn_config_not_implemented()
{
	rn_setSignum = (rn_setSignum_t) not_implemented_int;
	rn_init = (rn_init_t) not_implemented_int;
	rn_shutdown = (rn_shutdown_t) not_implemented_void;
	rn_prepare_fd_for_add = (rn_prepare_fd_for_add_t) not_implemented_void;
	rn_add = (rn_add_t) not_implemented_int;
	rn_del = (rn_del_t) not_implemented_int;
	rn_waitAndDispatchEvents = (rn_waitAndDispatchEvents_t) not_implemented_int;
	return 0;
}

void __attribute__ ((constructor)) rn_config_default()
{
	/* Try them best-to-worst until one works */
	if (!rn_config_sys_epoll())
		return;
	if (!rn_config_dev_epoll())
		return;
	if (!rn_config_sigio())
		return;
	/* If none of the real methods are supported, set up the dummy ones. */
	rn_config_not_implemented();
}
