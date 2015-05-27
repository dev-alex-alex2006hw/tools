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

/*
 * Simple test program for the rn socket readiness notification library.
 * Not really a good example; nearly all of the complexity in this file
 * is there to test rn, not to simply use it!
 * Requires chargen service.
 */

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <rn.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define TEST_BUF_SIZE	1024
#define BYTES_EXPECTED	65536

int fd;
int g_bytes_read=0;
int verbose = 1;

int onefd_callback(rn_pollevent_t *event)
{
	char buf[TEST_BUF_SIZE];
	int n;
	printf("onefd_callback: revents %x; ", event->revents);
	assert(event->fd == fd);
	/* Only news is that we can read. */
	if (event->revents & rn_POLLIN) {
		/* OS doesn't *have* to give us any more events on this fd 
		 * unless we keep reading until a short read or EWOULDBLOCK.
		 */
		int n_read = 0;
		do {
			n = read(fd, buf, TEST_BUF_SIZE);
			if (n > 0)
				n_read += n;
		} while (n == TEST_BUF_SIZE);
		g_bytes_read += n_read;
		printf("%d bytes read in this event", n_read);
		if (n == -1) {
			printf(", last read failed errno %d", errno);
			if (errno == EWOULDBLOCK) {
				printf("= EWOULDBLOCK");
				if (n_read == 0)
					printf(", spurious wakeup (ok)");
			}	
		}
		printf("\n");
	} else {
		switch (event->revents) {
			case rn_POLLOUT: 
				printf("rn_POLLOUT\n");
				break;
			default:
				printf("Event: %d\n", event->revents);
				break;
		}
	}
	return 0;
}

int pipe_fds[2];
enum eventkinds { EV_POLLIN, EV_POLLOUT, EV_POLLHUP };
int event_counts[EV_POLLHUP+1];
int event_total;

int pipe_callback(rn_pollevent_t *event)
{
	char buf[TEST_BUF_SIZE];
	int n;
	event_total++;
	printf("pipe_callback: fd %d, revents %x; event_total %d\n", event->fd, event->revents, event_total);
	assert(event->fd == pipe_fds[0] || event->fd == pipe_fds[1]);

	if (event->revents & rn_POLLIN) {
		event_counts[EV_POLLIN]++;
		printf("pipe_callback: pollin count now %d\n", event_counts[EV_POLLIN]);
		do {
			n = read(fd, buf, TEST_BUF_SIZE);
			printf("pipe_callback: read returns %d, errno %d\n", n, errno);
			g_bytes_read += n;
		} while (n == TEST_BUF_SIZE);
	}
	if (event->revents & rn_POLLOUT) {
		event_counts[EV_POLLOUT]++;
		printf("pipe_callback: pollout count now %d\n", event_counts[EV_POLLOUT]);
	}
	if (event->revents & rn_POLLHUP) {
		event_counts[EV_POLLHUP]++;
		printf("pipe_callback: pollhup count now %d\n", event_counts[EV_POLLHUP]);
	}
	return 0;
}


int main() 
{
	rn_t rns;
	const struct hostent *h;
	struct sockaddr_in dest;
	int err;
	int n;
	char buf[4096];
	time_t started;
	long delta;

	if (rn_init(&rns, 128)) {
		printf("FAIL: rn_init failed \n");
		exit(1);
	}
	if (rn_setSignum(&rns, SIGRTMIN)) {
		printf("FAIL: rn_sigio_setSignum failed \n");
		exit(1);
	}

	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd < 0) {
		perror("FAIL: socket failed");
		exit(1);
	}
	h = gethostbyname("localhost");
	if (h==NULL) {
		printf("FAIL: unknown host localhost");
		exit(1);
	}
	dest.sin_family = h->h_addrtype;
	memcpy((char *) &dest.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	dest.sin_port = htons(19);

	err=connect(fd, (struct sockaddr*) &dest, sizeof(dest));
	if (err < 0) {
		printf("The chargen tcp server needs to be enabled to run this demo.\n");
		printf("Enable the server by editing /etc/inetd.conf and then restarting inetd\n");
		perror("FAIL: connect failed");
		exit(1);
	}

	/* Put socket in non-blocking mode and also set any other 
	 * notification-type specific flags
	 */
	rn_prepare_fd_for_add(fd,getpid());

	/* Read anything that's there, because if we don't, the socket will 
	 * never make a transition from not-ready to ready, 
	 * and thus we will never get notified that it has become ready.
	 */
	while ((n=read(fd, buf, sizeof(buf))) > 0) {
#if 0
		buf[n]='\0';
		printf("read %d bytes: %s...\n",n,buf); 
#endif
	}
	rn_add(&rns, fd, onefd_callback, NULL);
	started = time(0);
	while ((time(0)-started < 10) && g_bytes_read < BYTES_EXPECTED) {
		err = rn_waitAndDispatchEvents(&rns, 2000);
		if (err && (err != EWOULDBLOCK)) {
			printf("FAIL: rn_waitAndDispatchEvents returns err %d\n", err);
			exit(1);
		}
	}

	if (g_bytes_read >= BYTES_EXPECTED)
		printf("Read %d bytes \n", g_bytes_read);
	else {
		printf("FAIL: Read only %d bytes \n", g_bytes_read);
		exit(1);
	}

	if (verbose)
		printf("Wait 1 second for more bytes to come in from chargen\n");
	sleep(2);

	/* OK, now let's make sure that rn sleeps.
	 * We'll use a socketpair for this (pipes aren't fully functional wrt SIGIO on linux kernel 2.4).
	 */
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, pipe_fds)) {
		printf("FAIL: socketpair");
		exit(1);
	}
	/* Sneakily don't remove old fd until new ones are created;
	 * this makes sure we don't think events for the old fd
	 * are from the new fds.  We need to check stale events for both cases,
	 * but at moment I'm interested in "fd no longer valid" case.
	 */
	rn_del(&rns, fd);
	/* VERY IMPORTANT: must close fd else it will emit signals forever.
	 * If you have DPRINT enabled, you'll see messages like
	 * waitForEvents: ignoring event on fd %d.  alloc %d used %d
	 * if you've forgotten to close an fd.  Should probably make
	 * waitAndDispatchEvents return an error in that case.
	 */
	close(fd);

	if (verbose)
		printf("fd closed.  Calling waitAndDispatchEvents to see if stale events for that fd come in.\n");
	err = rn_waitAndDispatchEvents(&rns, 500);

	/* Check to see which method we're using; they behave slightly differently */
	if ((void *)rn_init == (void *)rn_sigio_init) {
		if (err != EBADF) {
			printf("FAIL: using sigio, so expected EBADF from rn_waitAndDispatchEvents, got err %d\n", err);
			exit(1);
		}
		/* note: when run under strace, I didn't see the EBADF until the 2nd call to waitAndDisp.*/
	} else {
		if (err && err != EWOULDBLOCK) {
			printf("FAIL: not using sigio, so shouldn't have gotten EBADF from rn_waitAndDispatchEvents\n");
			exit(1);
		}
	}

	rn_prepare_fd_for_add(pipe_fds[0],getpid());
	rn_prepare_fd_for_add(pipe_fds[1],getpid());
	rn_add(&rns, pipe_fds[0], pipe_callback, NULL);
	rn_add(&rns, pipe_fds[1], pipe_callback, NULL);

	/* Die if no events in 30 seconds */
	alarm(30);

	if (verbose) 
		printf("Wait for all events on new pipe fds\n");
	started = time(0);
	do {
		int oldtotal = event_total;
		err = rn_waitAndDispatchEvents(&rns, 0);
		if (err && (err != EWOULDBLOCK)) {
			printf("FAIL: rn_waitAndDispatchEvents returns err %d\n", err);
			exit(1);
		}
		if (oldtotal == event_total)
			break;
		if (time(0)-started > 2) {
			printf("FAIL: slept when not expected, or looped for too long\n");
			exit(1);
		}
	} while (1);

	if (verbose) 
		printf("Verify that rn_waitAndDispatchEvents sleeps properly when there are no events\n");
	started = time(0);
	err=rn_waitAndDispatchEvents(&rns, 3000);
	if (err != EWOULDBLOCK) {
		printf("FAIL: return value of rn_waitAndDispatchEvents %d, expected EWOULDBLOCK\n", err);
		exit(1);
	}

	delta = time(0)-started;
	if (delta < 2 || delta > 4) {
		printf("FAIL: slept for wrong duration; delta is %ld, expected 2 to 4\n", delta);
		exit(1);
	}

	if (verbose)
		printf("Verify that closing one end of a pipe wakes up the other end\n");
	rn_del(&rns, pipe_fds[1]);
	close(pipe_fds[1]);

	/* verify that other end is readable according to select() */
	{
		fd_set foo;
		struct timeval tv;

		FD_ZERO(&foo);
		FD_SET(pipe_fds[0], &foo);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		n = select(pipe_fds[0]+1, &foo, 0, 0, &tv);
		if (n != 1 || !FD_ISSET(pipe_fds[0], &foo)) {
			printf("INTERNAL FAILURE: read end of pipe not ready for reading after peer closes\n");
			exit(2);
		}
	}

	event_counts[EV_POLLIN] = 0;
	started = time(0);
	do {
		int oldtotal = event_total;
		err = rn_waitAndDispatchEvents(&rns, 0);
		if (err && (err != EWOULDBLOCK)) {
			printf("FAIL: rn_waitAndDispatchEvents returns err %d\n", err);
			exit(1);
		}
		if (oldtotal == event_total)
			break;
		if (time(0)-started > 2) {
			printf("FAIL: slept when not expected, or looped for too long\n");
			exit(1);
		}
	} while (1);

	if (event_counts[EV_POLLHUP] == 0) {
		printf("FAIL: expected POLLHUP event when peer closes.\n");
		exit(1);
	}

	rn_shutdown(&rns);
	printf("PASS\n");
	return 0;
}

