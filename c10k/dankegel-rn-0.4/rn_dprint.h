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

#ifndef rn_dprint_h
#define rn_dprint_h

/* FIXME: prefix identifiers declared by this file with rn_ */

/* This file uses __VA_ARGS__, a C99 extension (see http://home.tiscalinet.ch/t_wolf/tw/c/c9x_changes.html#Preprocessor)
 * gcc 3.0 and later is fine; not sure when or if msvc will start supporting it.
 * It also tries to use the __attribute__ extension from gcc, if gcc is 3.2.0 or later.
 * See also http://gcc.gnu.org/cgi-bin/gnatsweb.pl?cmd=view%20audit-trail&database=gcc&pr=3481
 */

#include <stdio.h>
#include <rn_eclock.h>

#define __GCC_VERSION(major,minor,patchlevel)  (((major)*10000)+(minor*100)+(patchlevel))
#define __GCCV __GCC_VERSION(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)

#if defined(__GNUC__) && (__GCCV >= __GCC_VERSION(3,2,0))
#define attribute(...) __attribute__(__VA_ARGS__)
#else
#define attribute(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The default log function - in case you want to restore it.
 * If flags is nonzero, prefixes line with info about caller.
 */
attribute((format (printf, 5, 6))) void dprint_fn_default(int flags, int line, const char *file, const char *callername, const char *format, ...);

/* Set only via dprint_set_fn() */
extern attribute((format (printf, 5, 6))) void (*dprint_fn)(int flags, int line, const char *file, const char *callername, const char *format, ...);

#ifdef __cplusplus
}
#endif

/* Call this to install your own logging function.
 * You should declare yours exactly like dprint_fn_default above,
 * with extern "C", attribute, and everything; then pass
 * its name to dprint_set_fn().
 */
void dprint_set_fn(attribute((format (printf, 5, 6))) void (*fn)(int flags, int line, const char *file, const char *callername, const char *format, ...));

/* Helper macro for real DPRINT */
#define _DPRINT(...)      do { if (dprint_fn) (*dprint_fn)(1,__LINE__,__FILE__,__FUNCTION__, __VA_ARGS__); } while (0)

/* continue message started in last call to _DPRINT */
#define _DPRINT_MORE(...) do { if (dprint_fn) (*dprint_fn)(0,__LINE__,__FILE__,__FUNCTION__, __VA_ARGS__); } while (0)

/* Makefile will define dprint_ENABLED for debug builds */
/* #define dprint_ENABLED */
/* Developers may wish to rebuild with dprint_TRACE_ENABLED, but no standard build does it */
/* #define dprint_TRACE_ENABLED */

#ifdef dprint_ENABLED
#define DPRINT(...)   _DPRINT(__VA_ARGS__)
#define DPRINT_MORE(...)   _DPRINT_MORE(__VA_ARGS__)
#else
#define DPRINT(...) do { ; } while (0)
#define DPRINT_MORE(...) do { ; } while (0)
#endif

#define LOG_ERROR(...) _DPRINT(__VA_ARGS__)

#ifdef dprint_TRACE_ENABLED
#define LOG_TRACE(...) _DPRINT(__VA_ARGS__)
#else
#define LOG_TRACE(...) do { ; } while (0)
#endif

#endif
