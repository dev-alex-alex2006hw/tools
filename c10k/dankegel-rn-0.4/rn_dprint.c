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

#include <stdarg.h>
#include <stdio.h>
#include "rn_dprint.h"
#include "rn_eclock.h"

/* Pointer to the current logging function */
void (*dprint_fn)(int cont, int line, const char *file, const char *callername, const char *format, ...) = dprint_fn_default;

/* Function to set the current logging function pointer */
void dprint_set_fn(attribute((format (printf, 5, 6))) void (*fn)(int cont, int line, const char *file, const char *callername, const char *format, ...))
{
	dprint_fn = fn;
}

/* Default logging function. 
 * You can override this with dprint_set_fn().
 * If flags is nonzero, prefixes line with info about caller.
 */
void dprint_fn_default(int flags, int line, const char *file, const char *function, const char *format, ...)
{
	va_list ap;

	/* Eventually, we could have one flag bit for each of these items, and the thread id, too */
	if (flags)
		printf("%d:%d:%s:%s\t", (int)eclock(), line, file, function);

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}
