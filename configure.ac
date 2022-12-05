dnl  aprs-weather-submit
dnl  Copyright (c) 2019-2022 Colin Cogle <colin@colincogle.name>
dnl
dnl  This file, configure.ac, is part of hpreadymsg.
dnl  <https://github.com/rhymeswithmogul/aprs-weather-submit>
dnl
dnl  This program is free software: you can redistribute it and/or modify it
dnl  under the terms of the GNU General Public License as published by the Free
dnl  Software Foundation, either version 2 of the License, or (at your option)
dnl  any later version.
dnl
dnl  This program is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl  for more details.
dnl
dnl  You should have received a copy of the GNU General Public License
dnl  along with this program. If not, see <http://gnu.org/licenses/>.

AC_INIT([hpreadymsg], [1.0], [https://github.com/rhymeswithmogul/JetDirect-Display-Hack/])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AC_PREREQ
AC_PROG_INSTALL

dnl  Check for a C99 compiler.
AC_LANG([C])
AC_PROG_CC
AC_PROG_CC_C_O
AC_C_CONST

dnl  Check for install.
AC_PROG_INSTALL

dnl  Define types
AC_TYPE_SIZE_T

dnl  C compiler flags:
dnl    -std=gnu99    Compile C99, with GNU extensions (for getaddrinfo,
dnl                  gai_strerror, freeaddrinfo, struct addrinfo)
dnl    -Wall         Complain heavily.
dnl    -Wextra       Complain very heavily.
dnl    -Werror       Make all warnings errors.
dnl    -O2           Optimize (unless we're debugging)
AM_CFLAGS="-std=gnu99 -Wall -Wextra -Werror -O2"
AC_SUBST([AM_CFLAGS])


dnl  Check for the standard I/O functions, plus C99's snprintf().
AC_CHECK_HEADER(stdio.h,  [], AC_MSG_ERROR([stdio.h is required to build this package.]))
AC_CHECK_FUNC([fprintf],  [], AC_MSG_ERROR([fprintf() is required to build this package but was not found in stdio.h.]))
AC_CHECK_FUNC([printf],   [], AC_MSG_ERROR([printf() is required to build this package but was not found in stdio.h.]))

dnl  Check for string functions.
AC_CHECK_HEADER(string.h, [], AC_MSG_ERROR([string.h is required to build this package.]))
AC_CHECK_FUNC([strcpy],   [], AC_MSG_ERROR([strcpy() is required to build this package but was not found in string.h.]))
AC_CHECK_FUNC([strlen],   [], AC_MSG_ERROR([strlen() is required to build this package but was not found in string.h.]))
AC_CHECK_FUNC([strcat],  [], AC_MSG_ERROR([strcat() is required to build this package but was not found in string.h.]))
AC_CHECK_FUNC([strncat],  [], AC_MSG_ERROR([strncat() is required to build this package but was not found in string.h.]))

AC_CHECK_HEADERS(
	[arpa/inet.h],
	[],
	AC_MSG_ERROR([Cannot compile because <arpa/inet.h> is missing.])
)
AC_CHECK_HEADERS(
	[netdb.h],
	[],
	AC_MSG_ERROR([Cannot compile because <netdb.h> is missing.])
)
AC_CHECK_HEADERS(
	[netinet/in.h],
	[],
	AC_MSG_ERROR([Cannot compile because <netinet/in.h> is missing.])
)
AC_CHECK_HEADERS(
	[sys/socket.h],
	[],
	AC_MSG_ERROR([Cannot compile because <sys/socket.h> is missing.])
)
AC_CHECK_HEADERS(
	[sys/types.h],
	[],
	AC_MSG_ERROR([Cannot compile because <sys/types.h> is missing.])
)
AC_CHECK_HEADERS(
	[unistd.h],
	[],
	AC_MSG_ERROR([Cannot compile because <unistd.h> is missing.])
)

AC_ARG_ENABLE([debug], 
    [AS_HELP_STRING([--enable-debug], [build with added debugging output])],
    [enable_debug="yes"],
    [enable_debug="no"]
)
AS_IF([test "x$enable_debug" = "xyes"], [
    AC_DEFINE([DEBUG], 1, [Build with symbols and debugging output.])
    CFLAGS="$CFLAGS -O0 -g3"
])

dnl  Done!
AC_SUBST(CFLAGS)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
AC_MSG_RESULT([
############################
Run make to build this app.

OPTIONS:
  Debugging output: $enable_debug
###########################
])