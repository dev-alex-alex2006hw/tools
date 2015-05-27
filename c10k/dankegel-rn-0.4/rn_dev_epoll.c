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
#include <linux/poll.h>	/* careful - might be wrong */
#include <rn_dev_epoll.h>
#include <rn_dprint.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#ifdef HAVE_LINUX_EVENTPOLL_H_EP_ALLOC

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/* FIXME: linux/eventpoll.h macros should take value of PAGE_SIZE at runtime */
#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#include <linux/eventpoll.h>

int rn_dev_epoll_init(struct rn_dev_epoll *this, int maxfds)
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

	if ((this->epfd = open("/dev/epoll", O_RDWR)) == -1) {
		perror("open() /dev/epoll");
		return -1;
	}
	if (ioctl(this->epfd, EP_ALLOC, this->maxfds)) {
		perror("ioctl() /dev/epoll");
		close(this->epfd);
		return -1;
	}
	if ((this->epmap = (char *) mmap(NULL, EP_MAP_SIZE(this->maxfds), PROT_READ, MAP_PRIVATE, this->epfd, 0)) == (char *) -1) {
		perror("mmap() /dev/epoll");
		ioctl(this->epfd, EP_FREE, 0);
		close(this->epfd);
		return -1;
	}
	return 0;
}

void rn_dev_epoll_shutdown(struct rn_dev_epoll *this)
{
	int i;

	for (i=this->m_fds_alloc-1; (i >= 0) && (this->m_fds_used > 0); i--)
		if (this->m_fds[i].pfn)
			rn_dev_epoll_del(this, i);

	if (this->m_fds) {
		free(this->m_fds);
		this->m_fds = NULL;
	}

	munmap(this->epmap, EP_MAP_SIZE(this->maxfds));
	ioctl(this->epfd, EP_FREE, 0);
	close(this->epfd);
}

int rn_dev_epoll_prepare_fd_for_add(int fd, int pid)
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

int rn_dev_epoll_add(struct rn_dev_epoll *this,int fd, rn_callback_fn_t pfn, void *data)
{
	int i, n;
	int err;
	struct pollfd pfd;

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

	pfd.fd = fd;
	pfd.events = POLLIN | POLLOUT | POLLERR | POLLHUP;
	pfd.revents = 0;
	if (write(this->epfd, &pfd, sizeof(pfd)) != sizeof(pfd)) {
		err = errno;
		LOG_ERROR("add: write(fd %d...) returns err %d\n",
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

int rn_dev_epoll_del(struct rn_dev_epoll *this,int fd)
{
	int err;
	struct pollfd pfd;

	DPRINT("del(fd %d)\n", fd);

	/* Sanity checks */
	if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0)) {
		LOG_ERROR("del(fd %d): fd out of range\n", fd);
		return EINVAL;
	}

	pfd.fd = fd;
	pfd.events = POLLREMOVE;
	pfd.revents = 0;
	if (write(this->epfd, &pfd, sizeof(pfd)) != sizeof(pfd)) {
		err = errno;
		LOG_ERROR("del: write(fd %d, ...) returns err %d\n", fd, err);
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
 @return 0 on success, EWOULDBLOCK if no events ready, EBADF if you forgot to close an fd after rn_del()
 */
int rn_dev_epoll_waitAndDispatchEvents(struct rn_dev_epoll *this, int timeout_millisec)
{
	struct evpoll evp;
	struct pollfd *pfds;
	rn_pollevent_t event;
	int nfds;
	int saw_stale = FALSE;
	int handled = FALSE;

	evp.ep_timeout = timeout_millisec;
	evp.ep_resoff = 0;
	LOG_TRACE("Calling epoll...\n");
	nfds = ioctl(this->epfd, EP_POLL, &evp);
	LOG_TRACE("epoll returns %d fds\n", nfds);
	pfds = (struct pollfd *) (this->epmap + evp.ep_resoff);
	assert(nfds < MAX_FDS_IN_EVENTPOLL);
	for (; nfds > 0; nfds--, pfds++) {
		int fd = pfds->fd;
		if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0) || !this->m_fds[fd].pfn) {
			DPRINT("waitForEvents: ignoring event on fd %d.  alloc %d used %d\n", 
				fd, this->m_fds_alloc, this->m_fds_used);
			/* silently ignore.  Might be stale (aren't time skews fun?) */
			saw_stale = TRUE;
			continue;
		}
		event.fd = fd;
		event.revents = pfds->revents & (POLLIN|POLLPRI|POLLOUT|POLLERR|POLLHUP|POLLNVAL);
		event.client = this->m_fds[fd];
		DPRINT("fd %d, revents %x\n", pfds->fd, pfds->revents);
		event.client.pfn(&event);
		handled = TRUE;
	}

	if (saw_stale)
		return EBADF;
	if (!handled)
		return EWOULDBLOCK;
	return 0;
}

#else
enum { foo } empty;	/* ansi c forbids empty files */
#endif
