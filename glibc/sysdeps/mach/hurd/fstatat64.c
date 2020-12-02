/* Get information about file named relative to open directory.  Hurd version.
   Copyright (C) 2006-2020 Free Software Foundation, Inc.
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

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <hurd.h>
#include <hurd/fd.h>

/* Get information about the file descriptor FD in BUF.  */
int
__fstatat64 (int fd, const char *filename, struct stat64 *buf, int flag)
{
  error_t err;
  io_t port;

  port = __file_name_lookup_at (fd, flag, filename, 0, 0);
  if (port == MACH_PORT_NULL)
    return -1;

  err = __io_stat (port, buf);
  __mach_port_deallocate (__mach_task_self (), port);

  return __hurd_fail (err);
}
libc_hidden_def (__fstatat64)
weak_alias (__fstatat64, fstatat64)
