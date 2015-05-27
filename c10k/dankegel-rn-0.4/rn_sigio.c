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
#include <rn_eclock.h>
#include <rn_sigio.h>
#include <signal.h>
#include <stdlib.h>

#ifdef HAVE_F_SETSIG

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

int rn_sigio_init(struct rn_sigio *this, int maxfds)
{
	int i;

	(void) maxfds;

	DPRINT("init()\n");

	this->m_fds_used = 0;
	this->m_fds_alloc = 16;
	this->m_fds = (rn_client_t *)malloc(sizeof(rn_client_t) * this->m_fds_alloc);
	if (!this->m_fds)
		return ENOMEM;
	
	for (i=this->m_fds_used; i<this->m_fds_alloc; i++) {
		this->m_fds[i].pfn = NULL;
		this->m_fds[i].data = NULL;
	}

	return 0;
}

int rn_sigio_setSignum(struct rn_sigio *this,int signum)
{
	DPRINT("registering %d as the signal to get events on.\n", signum);
	this->m_signum = signum;
	sigemptyset(&this->m_sigset);
	sigaddset(&this->m_sigset, signum);
	sigaddset(&this->m_sigset, SIGIO);
	return sigprocmask(SIG_BLOCK, &this->m_sigset, NULL);
}

void rn_sigio_shutdown(struct rn_sigio *this)
{
	int i;
	for (i=this->m_fds_alloc-1; (i >= 0) && (this->m_fds_used > 0); i--)
		if (this->m_fds[i].pfn)
			rn_sigio_del(this, i);

	signal(this->m_signum, SIG_IGN);	/* POSIX says this clears the queue */
	/* Can't leave signal ignored, or it might be.  (POSIX is fuzzy here.) */
	signal(this->m_signum, SIG_DFL);

	/* re-enable the signals we blocked
	 * FIXME: is this right?
	 */
	sigprocmask(SIG_UNBLOCK, &this->m_sigset, NULL);

	if (this->m_fds) {
		free(this->m_fds);
		this->m_fds = NULL;
	}
}

int rn_sigio_prepare_fd_for_add(int fd, int pid)
{
	
	int flags;

	if (fcntl(fd, F_SETOWN, pid) < 0) {
		int err = errno;
		LOG_ERROR("add: fcntl(fd %d, F_SETOWN, %d) returns err %d\n", fd, pid, err);
		return err;
	}

	/* FIXME: This is correct right now on Linux. May not be so later on */
	flags = O_RDWR | O_NONBLOCK | O_ASYNC;

	if (fcntl(fd, F_SETFL, flags) < 0) {
		int err = errno;
		LOG_ERROR("fcntl(fd %d, F_SETFL, 0x%x) returns err %d\n", fd, flags, err);
		return err;
	}
	return 0;
}

int rn_sigio_add(struct rn_sigio *this,int fd, rn_callback_fn_t pfn, void *data)
{
	int i, n;
	int err;

	/* Resize array indexed by fd if fd is beyond what we've seen. */
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

	/* Set this fd to emit the right signal. */
	if (fcntl(fd, F_SETSIG, this->m_signum) < 0) {
		err = errno;
		LOG_ERROR("add: fcntl(fd %d, F_SETSIG, %d) returns err %d\n",
				fd, this->m_signum, err);
		return err;
	}

	/* Update limits. */
	this->m_fds_used++;

	/* Start out claiming "all ready", and let user program try 
	   reading/writing/accept/connecting.  An EWOULDBLOCK should be harmless;
	   the user must then call clearReadiness() to tell us we were wrong.
	   This should handle the case where the fd is already ready for something
	   when we start.  (FIXME: Could call poll() here, instead.  Should we?)
	*/

	this->m_fds[fd].pfn = pfn;
	this->m_fds[fd].data = data;

	DPRINT("add(%d, %p, %p) this->m_fds_used %d\n", fd, pfn, data, this->m_fds_used);

	return 0;
}

int rn_sigio_del(struct rn_sigio *this,int fd)
{
	int err;
	int flags;

	DPRINT("del(fd %d)\n", fd);

	/* Sanity checks */
	if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0)) {
		LOG_ERROR("del(fd %d): fd out of range\n", fd);
		return EINVAL;
	}

#if 0	/* user must close */
	/* Set this fd to no longer emit signals. */
	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0) {
		err = errno;
		LOG_ERROR("del: fcntl(fd %d, F_GETFL) returns err %d\n", fd, err);
		return err;
	}
	flags &= ~O_ASYNC;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		err = errno;
		LOG_ERROR("del: fcntl(fd %d, F_SETFL, 0x%x) returns err %d\n",
				fd, flags, err);
		return err;
	}
#else
	(void) err;
	(void) flags;
#endif

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
int rn_sigio_waitAndDispatchEvents(struct rn_sigio *this, int timeout_millisec)
{
	int fd;
	int signum;
	siginfo_t info;
	struct timespec timeout;
	rn_pollevent_t event;
	int overflowed = FALSE;
	int handled = 0;
	int saw_stale = FALSE;

	timeout.tv_sec = (unsigned int)timeout_millisec / 1000U;
	timeout.tv_nsec = ((unsigned int)timeout_millisec % 1000U) * 1000000;

	/* Pull signals off the queue until we would block. */
	do {
		DPRINT("calling sigtimedwait with timeout %lu,%lu\n", 
			(unsigned long)timeout.tv_sec, (unsigned long)timeout.tv_nsec);
		signum = sigtimedwait(&this->m_sigset, &info, &timeout);
		/* must do this, since caller may want quicker timeout
		 * as a result of our first few callbacks
		 */
		timeout.tv_sec = 0;
		timeout.tv_nsec = 0;
		if (signum == -1)
		    DPRINT("sigtimedwait returns -1, errno %d\n", errno);
		else
		    DPRINT("sigtimedwait returns %d, fd %d, band %lx\n",
			signum, info.si_fd, info.si_band);
		if (signum == -1) 
			break;
		if (signum == SIGIO) {
			/* uh-oh. the realtime signal queue overflowed.  ditch all
			 * remaining signals, and call poll() to get current status.
			 */
			overflowed = TRUE;
			break;
		}

		assert(signum == this->m_signum);
		/* Remember the new event */
		fd = info.si_fd;
		if ((fd < 0) || (fd >= this->m_fds_alloc) || (this->m_fds_used == 0) || !this->m_fds[fd].pfn) {
			DPRINT("waitForEvents: ignoring event on fd %d.  alloc %d used %d\n", 
				fd, this->m_fds_alloc, this->m_fds_used);
			/* silently ignore.  Might be stale (aren't time skews fun?) */
			saw_stale = TRUE;
			continue;
		}
		event.fd = fd;
		event.revents = info.si_band & (POLLIN|POLLPRI|POLLOUT|POLLERR|POLLHUP|POLLNVAL);
		event.client = this->m_fds[fd];
		event.client.pfn(&event);
	} while (handled++ < 200);

	if (overflowed) {
		rn_pollevent_t event;
		DPRINT("waitForEvents: SIGIO received.  Normal under very heavy load.\n");

		/* We missed some events.  Ditch remaining signals.  */
		signal(this->m_signum, SIG_IGN);	/* POSIX says this clears the queue */
		/* Make sure that cleared the queue.  (Note that timeout is zero here.)
		 * assert(sigtimedwait(&this->m_sigset, &info, &timeout) != this->m_signum);
		 * Can't leave signal ignored, or it might be.  (POSIX is fuzzy here.)
		 */
		signal(this->m_signum, SIG_DFL);

		/* send 'everything ready' to all clients. */
		for (fd=0; fd<this->m_fds_alloc; fd++) {
			if (this->m_fds[fd].pfn) {
				event.fd = fd;
				event.revents = (POLLIN|POLLOUT);
				event.client = this->m_fds[fd];
				event.client.pfn(&event);
			}
		}
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
