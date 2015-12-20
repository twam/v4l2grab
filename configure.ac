#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([v4l2grab], [m4_esyscmd_s([git describe --always --tag --dirty 2>/dev/null])], [Tobias_Mueller@twam.info])

# prepare for automake
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([yuv.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([jpeg], [jpeg_start_compress])
AC_CHECK_LIB([v4l2], [v4l2_open])
AC_SEARCH_LIBS([clock_gettime],[rt],,
               [AC_MSG_ERROR([no library contains clock_gettime])])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h string.h sys/ioctl.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getpagesize select strerror])
AC_CHECK_FUNCS([clock_gettime])

AC_OUTPUT
