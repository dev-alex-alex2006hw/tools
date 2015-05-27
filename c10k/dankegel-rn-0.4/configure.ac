AC_PREREQ(2.53)
AC_INIT(rn,0.3,bug-rn@kegel.com)
AC_CONFIG_SRCDIR(rn.c)
AC_CONFIG_HEADERS(rn_config.h)
AC_COPYRIGHT([Copyright 2003, Ixia Communications.  Copyright 2002-2003, Dan Kegel])
AC_PROG_CC
AC_LANG(C)

AC_DEFINE(_GNU_SOURCE, 1, [Need glibc/linux extensions, e.g. F_SETSIG])

dnl if sys/epoll.h exists, we can try using modern sys_epoll
dnl Note that just because the header is there, doesn't mean the functions are defined or work
AC_CHECK_HEADERS(sys/epoll.h)

dnl Check to see if -lepoll is needed to use the sys_epoll functions
AC_SEARCH_LIBS(epoll_create, epoll)

dnl Check to see if sys_epoll functions can be linked to
AC_CHECK_FUNCS(epoll_create)

dnl if EP_ALLOC is declared in linux/eventpoll.h, we can try using "classic" /dev/epoll
dnl There was a brief time where eventpoll.h existed, but used a different interface;
dnl if anyone cares about it, we could also support that flavor of epoll.
dnl I only support classic /dev/epoll because of an existing project that uses it.
AC_CHECK_DECL(EP_ALLOC,[AC_DEFINE(HAVE_LINUX_EVENTPOLL_H_EP_ALLOC,1,[Classic /dev/epoll])],[],[#include <linux/eventpoll.h>])

dnl See if the toolchain knows about the F_SETSIG fcntl option used in Linux 2.4 and up 
dnl to do enhanced sigio readiness notification
AC_CHECK_DECL(F_SETSIG,[AC_DEFINE(HAVE_F_SETSIG,1,[F_SETSIG, needed for enhanced sigio])],[],[#include <fcntl.h>])

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
