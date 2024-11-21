#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0.0], [bozin2002@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Define options
AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable readline instead of getline]),
    AC_DEFINE(HAVE_READLINE,[],[input by readline insted of getline])
)
AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline], [disable support for readline])],
    [with_readline=false],
    [with_readline=true]
)

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Librhash is needed])])
AS_IF(
    [test x$with_readline = xtrue],
    [AC_CHECK_LIB([readline],[readline],[],[AC_MSG_ERROR([Libreadline is needed])])]
)

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h string.h rhash.h readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
