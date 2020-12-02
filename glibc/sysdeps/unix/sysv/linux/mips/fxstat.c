/* fxstat using old-style Unix stat system call.
   Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <sys/stat.h>
#include <fcntl.h>
#include <kernel_stat.h>
#include <sysdep.h>
#include <xstatconv.h>
#include <shlib-compat.h>

#if SHLIB_COMPAT(libc, GLIBC_2_0, GLIBC_2_33)

/* Get information about the file NAME in BUF.  */
int
attribute_compat_text_section
__fxstat (int vers, int fd, struct stat *buf)
{
  switch (vers)
    {
    case _STAT_VER_KERNEL:
      return INLINE_SYSCALL_CALL (fstat, fd, buf);

    default:
      {
	struct kernel_stat kbuf;
	int r = INTERNAL_SYSCALL_CALL (fstat, fd, &kbuf);
	return r ?: __xstat_conv (vers, &kbuf, buf);
      }
    }
}

compat_symbol (libc, __fxstat, __fxstat, GLIBC_2_0);

#endif
