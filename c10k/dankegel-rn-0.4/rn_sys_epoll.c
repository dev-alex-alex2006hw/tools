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

#include <rn_config.h>	/* must come first */

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <rn_dprint.h>
#include <rn_sys_epoll.h>
#include <stdlib.h>
#include <stdint.h>	/* must come before sys/epoll.h to deal with buglet in glibc-2.3.2 */
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#if defined(HAVE_SYS_EPOLL_H) && defined(HAVE_EPOLL_CREATE)

/* in case we're compiled on a somewhat old system */
#ifndef EPOLLET
#define EPOLLET (1 << 31)
#endif

/* FIXME: linux/eventpoll.h macros should take value of PAGE_SIZE at runtime */
#define PAGE_SIZE sysconf(_SC_PAGESIZE)
/* FIXME: should not use hardcoded limit or static array */
#define MAX_EVENTS 1024
struct epoll_event events[MAX_EVENTS];
/* #include <linux/eventpoll.h>*/

int rn_sys_epoll_init(struct rn_sys_epoll *this, int maxfds)
{
	int i;

	DPRINT("init()\n");

	/* unfortunate kludge in epoll.  May be removed eventually. */
	this->maxfds = maxfds;

	this->m_fds_used = 0;
	this->m_fds_alloc = 16;
	this->m_fds = (rn_client_t *)malloc(sizeof(rn_client_t) * this->m_fds_alloc);
	if (!this->m_fds)
		return ENOMEM;
	
	for (i=this->m_fds_used; i<this->m_fds_alloc; i++) {
		this->m_fds[i].pfn = NULL;
		this->m_fds[i].data = NULL;
	}

	this->epfd = epoll_create(maxfds);

	if (this->epfd == -1)
		return errno;

	return 0;
}

void rn_sys_epoll_shutdown(struct rn_sys_epoll *this)
{
	int i;

	for (i=this->m_fds_alloc-1; (i >= 0) && (this->m_fds_used > 0); i--)
		if (this->m_fds[i].pfn)
			rn_sys_epoll_del(this, i);

	if (this->m_fds) {
		free(this->m_fds);
		this->m_fds = NULL;
	}

	close(this->epfd);
	this->epfd = -1;
}

int rn_sys_epoll_prepare_fd_for_add(int fd, int pid)
{
	
	/* FIXME: This is correct right now on Linux. May not be so later on */
	int flags = O_RDWR | O_NONBLOCK;
	
	(void) pid;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		int err = errno;
		LOG_ERROR("fcntl(fd %d, F_SETFL, 0x%x) returns err %d\n",
				fd, flags, err);
		return err;
	}
	return 0;
}

int rn_sys_epoll_add(struct rn_sys_epoll *this,int fd, rn_callback_fn_t pfn, void *data)
{
	int i, n;
	int err;
	struct epoll_event efd;

	if (fd >= this->m_fds_alloc) {
		rn_client_t *newfds;
		n = this->m_fds_alloc * 2;
		if (n < fd + 1)
			n = fd + 1;

		newfds = (rn_client_t *)realloc(this->m_fds, n * sizeof(rn_client_t));
		if (!newfds)
			return ENOMEM;

		for (i=this->m_fds_alloc; i<n; i++) {
			newfds[i].pfn = NULL;
			newfds[i].data = NULL;
		}

		this->m_fds = newfds;
		this->m_fds_alloc = n;
	}

	/* Looks like we can always specify EPOLLET even if using older epoll driver */
	efd.data.fd = fd;
	efd.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, fd, &efd) == -1 ) {
		err = errno;
		LOG_ERROR("add: epoll_ctl(fd %d...) returns err %d\n",
				fd, err);
		return err;
	}

	this->m_fds_used++;

	/* Start out claiming "all ready", and let user program try 
	 * reading/writing/accept/connecting.  An EWOULDBLOCK should be harmless;
	 * the user must then call clearReadiness() to tell us we were wrong.
	 * This should handle the case where the fd is already ready for something
	 * when we start.  (FIXME: Could call poll() here, instead.  Should we?)
	 */

	this->m_fds[fd].pfn = pfn;
	this->m_fds[fd].data = data;

	DPRINT("add(%d, %p, %p) this->m_fds_used %d\n", fd, pfn, data, this->m_fds_used);

	return 0;
}

int rn_sys_epoll_del(struct rn_sys_epoll *this,int fd)
{
	int err;
	struct epoll_event efd;

	DPRINT("del(fd %d)\n", fd);

	/* Sanity checks */
	if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0)) {
		LOG_ERROR("del(fd %d): fd out of range\n", fd);
		return EINVAL;
	}

	efd.data.fd = fd;
	efd.events = -1;
	if (epoll_ctl(this->epfd, EPOLL_CTL_DEL, fd, &efd) == -1 ) {
		err = errno;
		LOG_ERROR("del: epoll_ctl(fd %d, ...) returns err %d\n", fd, err);
		return err;
	}

	this->m_fds[fd].pfn = NULL;
	this->m_fds[fd].data = NULL;

	this->m_fds_used--;

	return 0;
}


/**
 Sleep at most timeout_millisec waiting for an I/O readiness event
 on the file descriptors we're watching.  
 Call each descriptor's pfn if it's ready.
 @return 0 on success, EWOULDBLOCK if no events ready
 */
int rn_sys_epoll_waitAndDispatchEvents(struct rn_sys_epoll *this, int timeout_millisec)
{
	struct epoll_event *efds = events;
	rn_pollevent_t event;
	int nfds;

	LOG_TRACE("Calling epoll...\n");
	nfds = epoll_wait(this->epfd, efds, MAX_EVENTS /*this->m_fds_used*/, timeout_millisec);
	LOG_TRACE("epoll returns %d fds. errno: %d\n", nfds,errno);
	assert(nfds <= this->m_fds_used);
	for (; nfds > 0; nfds--, efds++) {
		int fd = efds->data.fd;
		if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0) || !this->m_fds[fd].pfn) {
			DPRINT("waitForEvents: ignoring event on fd %d.  alloc %d used %d\n", 
				fd, this->m_fds_alloc, this->m_fds_used);
			/* silently ignore.  Might be stale (aren't time skews fun?) */
			continue;
		}
		event.fd = fd;
		event.revents = efds->events & (EPOLLIN|EPOLLPRI|EPOLLOUT|EPOLLERR|EPOLLHUP);
		event.client = this->m_fds[fd];
		DPRINT("fd %d, revents %x\n", efds->data.fd, efds->events);
		event.client.pfn(&event);
	}
	return 0;
}

#else
enum { foo } empty;	/* ansi c forbids empty files */
#endif
